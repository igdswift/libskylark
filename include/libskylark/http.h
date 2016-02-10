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

#ifndef LIBSKYLARK_HTTP_H
#define LIBSKYLARK_HTTP_H

#define VERBOSE                0
// TLS support with self-signed CA
#define SKIP_PEER_VERIFICATION 1
#define SKIP_HOST_VERIFICATION 1
// For retries and waiting
#define MAX_RETRY_COUNT        5
#define PUT_STATUS_OK          200
#define WAIT_INTERVAL          1000

#define ENCODING           "Transfer-Encoding: chunked"
#define ACCEPT_TYPE        "Accept: application/vnd.swiftnav.broker.v1+sbp"
#define CONTENT_TYPE       "Content-Type: application/vnd.swiftnav.broker.v1+sbp"
#define DEFAULT_DEVICE_UID "Device-Uid: aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa"
#define BROKER_ENDPOINT    "https://broker.testing.skylark.swiftnav.com"
#define USER_AGENT         "libskylark-agent/1.0"

size_t publish_callback(void *p, size_t size, size_t n, void *up);

size_t subscribe_callback(void *p, size_t size, size_t n, void *up);

void setup_broker(void);

int publish(char *uid, void *fd);

int subscribe(char *uid, void *fd);

#endif /* LIBSKYLARK_HTTP_H */
