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
#include <libskylark/serial.h>

START_TEST(test_serial_0)
{
}
END_TEST

Suite* serial_suite(void)
{
  Suite *s = suite_create("SERIAL stuff");
  TCase *tc_serial = tcase_create("SERIAL");
  tcase_add_test(tc_serial, test_serial_0);
  suite_add_tcase(s, tc_serial);
  return s;
}
