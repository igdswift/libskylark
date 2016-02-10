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

#ifndef LIBSKYLARK_SERIAL_H
#define LIBSKYLARK_SERIAL_H

#include <libserialport.h>

struct serial_device_t {
  char *port;
  struct sp_port *data;
};

int serial_open(struct serial_device_t *serial, int flags);

int serial_close(struct serial_device_t *serial);

int serial_set_params(struct serial_device_t *serial,
                      int baudrate,
                      int bits,
                      int parity,
                      int stopbits,
                      int flowcontrol,
                      int rts,
                      int dtr);

int serial_write_blocking(struct serial_device_t *serial,
                          const void *buf,
                          size_t count,
                          unsigned int timeout_ms);

int serial_write_nonblocking(struct serial_device_t *serial,
                             const void *buf,
                             size_t count);

int serial_read_nonblocking(struct serial_device_t *serial,
                            void *buf, size_t count);

#endif /* LIBSKYLARK_HTTP_H */
