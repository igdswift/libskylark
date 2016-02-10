/*
 * Copyright (C) 2016 Swift Navigation Inc.
 * Contact: Bhaskar Mookerji <mookerji@swift-nav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef LIBSKYLARK_LOGGING_H
#define LIBSKYLARK_LOGGING_H

#include <syslog.h>

#ifndef DEBUG
#define DEBUG 0
#endif

void start_logging(void);

void log_(int priority, const char *format, ...);

#ifdef DEBUG
#define log_debug(...)    log_(LOG_DEBUG, args)
#else
#define log_debug(...)
#endif

#define log_error(args...)   log_(LOG_ERR, args)

#define log_warn(args...)    log_(LOG_WARNING, args)

#define log_notice(args...)  log_(LOG_NOTICE, args)

#define log_info(args...)    log_(LOG_INFO, args)

#endif /* LIBSKYLARK_LOGGING_H */
