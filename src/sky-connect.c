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
#include <libskylark/http.h>
#include <libskylark/logging.h>
#include <libskylark/serial.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  start_logging();
  if (argc < 4)
  {
    printf("Usage: sky-connect <device-uid> <tty> <baudrate>\n");
    return -1;
  }
  char *uid  = argv[1];
  char *path = argv[2];
  int baud   = atoi(argv[3]);
  struct serial_device_t serial;
  serial.port = malloc(sizeof(char) * strlen(path));
  strcpy(serial.port, path);
  if (serial_open(&serial, SP_MODE_READ | SP_MODE_WRITE) < 0)
  {
    serial_close(&serial);
    return -DEVICE_CONN_ERROR;
  }
  int bits = 8;
  int parity = SP_PARITY_NONE;
  int stopbits = 1;
  int flowcontrol = 0;
  int rts = 0;
  int dtr = 1;
  if (serial_set_params(&serial, baud, bits, parity, stopbits,
                        flowcontrol, rts, dtr) < 0)
  {
    serial_close(&serial);
    return -DEVICE_CONF_ERROR;
  }
  setup_broker();
  if (publish(uid, (void *) &serial) < 0)
  {
    serial_close(&serial);
    return -CONNECTION_ERROR;
  }
  serial_close(&serial);
  return NO_ERROR;
}
