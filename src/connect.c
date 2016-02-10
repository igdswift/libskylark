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

#include <stdio.h>
#include <stdlib.h>
#include <libskylark/errno.h>
#include <libskylark/http.h>
#include <libskylark/logging.h>
#include <libskylark/serial.h>

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
  int fd = init_serial(path);
  if (fd < 0)
  {
    log_error("device");
    return -DEVICE_CONN_ERROR;
  }
  if (set_serial_baud_rate(fd, baud) < 0)
  {
    log_error("device");
    return -DEVICE_CONF_ERROR;
  }
  setup_broker();
  /* if (publish(uid, fd) < 0) */
  /* { */
  /*   log_error("network"); */
  /*   return -CONNECTION_ERROR; */
  /* } */
  if (subscribe(uid, fd) < 0)
  {
    log_error("network");
    return -CONNECTION_ERROR;
  }
  return NO_ERROR;
}
