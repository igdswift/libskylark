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

#include <libskylark/logging.h>
#include <stdarg.h>
#include <stdlib.h>

void start_logging(void)
{
  openlog("libskylark", LOG_PERROR | LOG_NDELAY | LOG_PID, LOG_USER);
  atexit(closelog);
}

void default_log(uint8_t priority, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsyslog(priority, format, args);
}
