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

#include <fcntl.h>
#include <libskylark/errno.h>
#include <libskylark/logging.h>
#include <libskylark/platform.h>
#include <libskylark/serial.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <termios.h>

int init_serial(char *path)
{
  int fd = open(path, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd < 0)
  {
    perror("open");
    return -DEVICE_CONN_ERROR;
  }
  struct termios termattr;
  bzero(&termattr, sizeof(struct termios));
  if (tcgetattr(fd, &termattr) < 0)
  {
    log_error("tcgetattr");
    return -DEVICE_CONN_ERROR;
  }
  termattr.c_cflag = CRTSCTS | CS8 | CLOCAL | CREAD;
  termattr.c_iflag = IGNPAR;
  termattr.c_oflag = 0;
  termattr.c_lflag = 0;
  cfsetispeed(&termattr, B38400);
  cfsetospeed(&termattr, B38400);
  termattr.c_cc[VMIN]  = 5;
  termattr.c_cc[VTIME] = 0;
  if (tcflush(fd, TCIFLUSH) < 0)
  {
    log_error("tcflush(TCIFLUSH)");
    return -DEVICE_CONF_ERROR;
  }
  if (tcsetattr(fd, TCSANOW, &termattr) < 0)
  {
    log_error("tcsetattr(TCSANOW)");
    return -DEVICE_CONF_ERROR;
  }
  return fd;
}

int set_serial_baud_rate(int fd, int baud)
{
#if defined(__linux__)
  struct serial_struct ser_info;
  if (ioctl(fd, TIOCGSERIAL, &ser_info) < 0) {
    return -DEVICE_CONF_ERROR;
  }
  ser_info.custom_divisor = ser_info.baud_base / baud;
  if (ioctl(fd, TIOCSSERIAL, &ser_info) < 0) {
    return -DEVICE_CONF_ERROR;
  }
  return fd;
#elif defined(__APPLE__)
  if (ioctl(fd, IOSSIOSPEED, &baud) < 0)
  {
    log_error("ioctl(IOSSIOSPEED)");
    return -DEVICE_CONF_ERROR;
  }
  return fd;
#else
#warning set_serial_baud_rate: unsupported platform
  return -UNSUPPORTED_PLATFORM;
#endif
}
