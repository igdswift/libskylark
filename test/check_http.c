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

#include <check.h>
#include <libskylark/http.h>

START_TEST(test_http_0)
{
}
END_TEST

Suite* http_suite(void)
{
  Suite *s = suite_create("HTTP stuff");
  TCase *tc_http = tcase_create("HTTP");
  tcase_add_test(tc_http, test_http_0);
  suite_add_tcase(s, tc_http);
  return s;
}
