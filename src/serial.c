/*
 * Copyright (C) 2016 Swift Navigation Inc.
 * Contact: Mark Fine <mfine@swift-nav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <libserialport.h>
#include <libskylark/errno.h>
#include <libskylark/logging.h>
#include <libskylark/serial.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int serial_open(struct serial_device_t *serial, int flags)
{
  if (!serial) {
    log_error("serial_open: invalid serial port device.");
    return -DEVICE_CONN_ERROR;
  }
  log_info("serial_open: opening serial port '%s' (flags %d).",
           serial->port, flags);
  sp_get_port_by_name(serial->port, &serial->data);
  int ret = sp_open(serial->data, flags);
  char *error;
  switch (ret) {
  case SP_ERR_ARG:
    log_error("serial_open: invalid serial port parameters.");
    return -DEVICE_CONF_ERROR;
  case SP_ERR_FAIL:
    error = sp_last_error_message();
    log_error("serial_open: error opening serial port (%d): %s.",
              sp_last_error_code(), error);
    sp_free_error_message(error);
    return -DEVICE_CONN_ERROR;
  }
  return NO_ERROR;
}

int serial_close(struct serial_device_t *serial)
{
  if (!serial) {
    log_error("serial_close: invalid serial port device.");
    return -DEVICE_CONN_ERROR;
  }
  if (!serial->data) {
    log_error("serial_close: cannot close unopened serial port %s.",
              serial->port);
    return -DEVICE_CONN_ERROR;
  }
  log_info("serial_close: closing serial port %s.", serial->port);
  int ret = sp_close(serial->data);
  char *error;
  switch (ret) {
  case SP_ERR_ARG:
    log_error("serial_close: attempt to close an invalid serial port.");
    return -DEVICE_CONF_ERROR;
  case SP_ERR_FAIL:
    error = sp_last_error_message();
    log_error("serial_close: error closing port (%d): %s.",
              sp_last_error_code(), error);
    sp_free_error_message(error);
    return -DEVICE_CONN_ERROR;
  }
  sp_free_port(serial->data);
  serial->data = NULL;
  return NO_ERROR;
}

int serial_set_params(struct serial_device_t *serial,
                      int baudrate,
                      int bits,
                      int parity,
                      int stopbits,
                      int flowcontrol,
                      int rts,
                      int dtr)
{
  if (!serial) {
    log_error("serial_set_params: invalid serial port device.");
    return -DEVICE_CONN_ERROR;
  }
  if (!serial->data) {
    log_error("serial_set_params: cannot configure unopened serial port %s.",
              serial->port);
    return -DEVICE_CONN_ERROR;
  }
  log_debug("serial_set_params: setting serial parameters on port %s.",
            serial->port);
  struct sp_port_config *config;
  sp_new_config(&config);
  sp_set_config_baudrate(config, baudrate);
  sp_set_config_bits(config, bits);
  sp_set_config_parity(config, parity);
  sp_set_config_stopbits(config, stopbits);
  sp_set_config_rts(config, flowcontrol == 1 ? SP_RTS_FLOW_CONTROL : rts);
  sp_set_config_cts(config, flowcontrol == 1 ? SP_CTS_FLOW_CONTROL : SP_CTS_IGNORE);
  sp_set_config_dtr(config, dtr);
  sp_set_config_dsr(config, SP_DSR_IGNORE);
  sp_set_config_xon_xoff(config, flowcontrol == 2 ? SP_XONXOFF_INOUT : SP_XONXOFF_DISABLED);
  int ret = sp_set_config(serial->data, config);
  sp_free_config(config);
  char *error;
  switch (ret) {
  case SP_ERR_ARG:
    log_error("serial_set_params: invalid serial port parameters.");
    return -DEVICE_CONF_ERROR;
  case SP_ERR_FAIL:
    error = sp_last_error_message();
    log_error("serial_set_params: error setting serial port parameters (%d): %s.",
              sp_last_error_code(), error);
    sp_free_error_message(error);
    return -DEVICE_CONN_ERROR;
  }
  return NO_ERROR;
}

static int _serial_write(struct serial_device_t *serial,
                         const void *buf, size_t count,
                         int nonblocking, unsigned int timeout_ms)
{
  if (!serial) {
    log_error("serial_write: invalid serial port device.");
    return -DEVICE_CONN_ERROR;
  }
  if (!serial->data) {
    log_error("serial_write: cannot use unopened serial port %s.", serial->port);
    return -DEVICE_CONN_ERROR;
  }
  int ret;
  if (nonblocking) {
    ret = sp_nonblocking_write(serial->data, buf, count);
  } else {
    ret = sp_blocking_write(serial->data, buf, count, timeout_ms);
  }
  char *error;
  switch (ret) {
  case SP_ERR_ARG:
    log_error("serial_write: invalid serial port parameters.");
    return -DEVICE_CONF_ERROR;
  case SP_ERR_FAIL:
    error = sp_last_error_message();
    log_error("serial_write: write error (%d): %s.", sp_last_error_code(), error);
    sp_free_error_message(error);
    return -DEVICE_CONN_ERROR;
  }
  return ret;
}

int serial_write_blocking(struct serial_device_t *serial,
                          const void *buf,
                          size_t count,
                          unsigned int timeout_ms)
{
  return _serial_write(serial, buf, count, 0, timeout_ms);
}

int serial_write_nonblocking(struct serial_device_t *serial,
                             const void *buf,
                             size_t count)
{
  return _serial_write(serial, buf, count, 1, 0);
}

static int _serial_read(struct serial_device_t *serial,
                 void *buf,
                 size_t count,
                 int nonblocking,
                 unsigned int timeout_ms)
{
  if (!serial) {
    log_error("serial_read_nonblocking: invalid serial port device.");
    return -DEVICE_CONN_ERROR;
  }
  if (!serial->data) {
    log_error("serial_read_nonblocking: cannot use unopened serial port %s.",
              serial->port);
    return -DEVICE_CONN_ERROR;
  }
  int ret;
  if (nonblocking) {
    ret = sp_nonblocking_read(serial->data, buf, count);
  } else {
    // TODO read or read_next? Bailing early is probably better than waiting.
    ret = sp_blocking_read(serial->data, buf, count, timeout_ms);
  }
  char *error;
  switch (ret) {
  case SP_ERR_ARG:
    log_error("serial_read_nonblocking: invalid serial port parameters.");
    return -DEVICE_CONF_ERROR;
  case SP_ERR_FAIL:
    error = sp_last_error_message();
    log_error("serial_read_nonblocking: read error (%d): %s.",
              sp_last_error_code(), error);
    sp_free_error_message(error);
    return -DEVICE_CONN_ERROR;
  }
  return ret;
}

int serial_read_blocking(struct serial_device_t *serial,
                         void *buf,
                         size_t count,
                         unsigned int timeout_ms) {
  return _serial_read(serial, buf, count, 0, timeout_ms);
}

int serial_read_nonblocking(struct serial_device_t *serial,
                            void *buf,
                            size_t count)
{
  return _serial_read(serial, buf, count, 1, 0);
}
