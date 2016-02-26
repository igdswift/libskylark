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

#ifndef LIBSKYLARK_ERRNO_H
#define LIBSKYLARK_ERRNO_H

#define NO_ERROR              0   /** No error occurred! */
#define GENERIC_ERROR         1   /** Generic error. */
#define NULL_VALUE_ERROR      2   /** A required arguments was null.*/
#define DEVICE_CONN_ERROR     3   /** Error connecting to device. */
#define DEVICE_CONF_ERROR     4   /** Error configuring device. */
#define CONNECTION_ERROR      5   /** Connection failed. */
#define SUBSCRIBE_ERROR       6   /** Subscribe failed. */
#define PUBLISH_ERROR         7   /** Publish failed. */
#define DISCONNECT_ERROR      8   /** Disconnect failed. */
#define SSL_CONNECT_ERROR     9   /** TLS handshake failed. */
#define SSL_CERT_ERROR       10   /** SSL certificate error */
#define UNSUBSCRIBE_ERROR    11   /** Unsubscribe failed. */
#define UNSUPPORTED_PLATFORM 12   /** Unsupported platform. */
#define UNSUPPORTED_PLATFORM 12   /** Unsupported platform. */

#endif /* LIBSKYLARK_ERRNO_H */
