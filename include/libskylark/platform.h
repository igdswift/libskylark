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

#ifndef LIBSKYLARK_PLATFORM_H
#define LIBSKYLARK_PLATFORM_H

#if defined(__linux__)
#include <linux/serial.h>
#elif defined(__APPLE__)
# include <IOKit/serial/ioss.h>
#else
#warning libskylark/serial.h: unsupported platform
#endif

#endif /* LIBSKYLARK_PLATFORM_H */
