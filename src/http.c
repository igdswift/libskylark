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

#include <curl/curl.h>
#include <libskylark/errno.h>
#include <libskylark/http.h>
#include <libskylark/logging.h>
#include <libskylark/serial.h>
#include <stdlib.h>
#include <unistd.h>

size_t publish_callback(char *p, size_t size, size_t n, void *up)
{
  if (size*n < 1)
  {
    return 0;
  }
  char buf;
  if (serial_read_nonblocking((struct serial_device_t *)up, &buf, 1) < 0)
  {
    log_error("publish_callback: serial_read_nonblocking");
    return 0;
  }
  *(char *)p = buf;
  return 1;
}

size_t subscribe_callback(char *p, size_t size, size_t n, void *up)
{
  if (serial_write_nonblocking((struct serial_device_t *)up, &p, size*n) < 0) {
    log_error("subscribe_callback: serial_write_nonblocking");
    return 0;
  }
  return size*n;
}

void setup(void)
{
  curl_global_init(CURL_GLOBAL_ALL);
}

void teardown(void)
{
  curl_global_cleanup();
}

int publish(const char *uid, void *fd, callback cb)
{
  CURL *curl = curl_easy_init();
  if (!curl)
  {
    return -GENERIC_ERROR;
  }
  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, ENCODING);
  chunk = curl_slist_append(chunk, CONTENT_TYPE);
  char buf[sizeof(DEFAULT_DEVICE_UID)];
  sprintf(buf, "Device-Uid: %s", uid);
  chunk = curl_slist_append(chunk, buf);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER,   chunk);
#ifdef VERBOSE
  curl_easy_setopt(curl, CURLOPT_VERBOSE,      1);
#endif
#ifdef SKIP_PEER_VERIFICATION
  // In the case that the host is using a self-signed CA.
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
  curl_easy_setopt(curl, CURLOPT_URL,          BROKER_ENDPOINT);
  curl_easy_setopt(curl, CURLOPT_PUT,          1);
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, cb);
  curl_easy_setopt(curl, CURLOPT_READDATA,     fd);
  curl_easy_setopt(curl, CURLOPT_USERAGENT,    USER_AGENT);
  int res;
  for (int i = 0; i < MAX_RETRY_COUNT; ++i) {
    // This is actually a blocking put and should be made into a
    // non-blocking PUT.
    res = curl_easy_perform(curl);
    int http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (res == CURLE_OK && http_code == PUT_STATUS_OK) {
      curl_easy_cleanup(curl);
      return NO_ERROR;
    } else {
      log_info("publish: retrying!");
      sleep(WAIT_INTERVAL);
    }
  }
  log_error(curl_easy_strerror(res));
  return -CONNECTION_ERROR;
}

int subscribe(const char *uid, void *fd, callback cb)
{
  CURL *curl = curl_easy_init();
  if (!curl)
  {
    return -GENERIC_ERROR;
  }
  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, ENCODING);
  chunk = curl_slist_append(chunk, ACCEPT_TYPE);
#ifdef PROXY
  chunk = curl_slist_append(chunk, "Pragma: proxy");
#endif
  char buf[sizeof(DEFAULT_DEVICE_UID)];
  log_info("Subscribing: %s", uid);
  sprintf(buf, "Device-Uid: %s", uid);
  chunk = curl_slist_append(chunk, buf);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER,   chunk);
#ifdef VERBOSE
  curl_easy_setopt(curl, CURLOPT_VERBOSE,      1);
#endif
#ifdef SKIP_PEER_VERIFICATION
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
  curl_easy_setopt(curl, CURLOPT_URL,           BROKER_ENDPOINT);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
  curl_easy_setopt(curl, CURLOPT_USERAGENT,     USER_AGENT);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA,     fd);
  int res = curl_easy_perform(curl);
  if (res != CURLE_OK)
  {
    log_error(curl_easy_strerror(res));
    return -CONNECTION_ERROR;
  }
  curl_easy_cleanup(curl);
  return NO_ERROR;
}
