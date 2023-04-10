#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(from_decimal_to_float) {
  s21_decimal x = {{4294967295, 4294967295, 4294967295, 2149318656}};
  float y;
  s21_from_decimal_to_float(x, &y);
  ck_assert_float_eq(-7.9228162514264337593543950335, y);
}
END_TEST

START_TEST(from_decimal_to_float2) {
  s21_decimal x = {{0, 0, 0, 0}};
  float y;
  s21_from_decimal_to_float(x, &y);
  ck_assert_float_eq(0, y);
}
END_TEST

START_TEST(from_decimal_to_int) {
  s21_decimal x = {{0, 0, 0, 0}};
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(0, y);
}
END_TEST

START_TEST(from_decimal_to_int2) {
  s21_decimal x = {{INT_MAX, 0, 0, 2147483648}};
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(-INT_MAX, y);
}
END_TEST

START_TEST(from_float_to_decimal) {
  s21_decimal x;
  float y = 0.0;
  s21_from_float_to_decimal(y, &x);
  ck_assert_int_eq(0, x.bits[0]);
  ck_assert_int_eq(0, x.bits[1]);
  ck_assert_int_eq(0, x.bits[2]);
  ck_assert_int_eq(0, x.bits[3]);
}
END_TEST

START_TEST(from_float_to_decimal2) {
  s21_decimal x;
  float y = -0.000000026262;
  s21_from_float_to_decimal(y, &x);
  ck_assert_int_eq(26262, x.bits[0]);
  ck_assert_int_eq(0, x.bits[1]);
  ck_assert_int_eq(0, x.bits[2]);
  ck_assert_int_eq(2148270080, x.bits[3]);
}
END_TEST

START_TEST(from_float_to_decimal3) {
  s21_decimal x;
  float y = 19393939393993993.95757575;
  s21_from_float_to_decimal(y, &x);
  ck_assert_int_eq(2290010112, x.bits[0]);
  ck_assert_int_eq(4515503, x.bits[1]);
  ck_assert_int_eq(0, x.bits[2]);
  ck_assert_int_eq(0, x.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal) {
  int x = 555655555;
  s21_decimal y;
  s21_from_int_to_decimal(x, &y);
  ck_assert_int_eq(abs(x), y.bits[0]);
  ck_assert_int_eq(0, y.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal2) {
  int x = -555655555;
  s21_decimal y;
  s21_from_int_to_decimal(x, &y);
  ck_assert_int_eq(abs(x), y.bits[0]);
  ck_assert_int_eq(2147483648, y.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal3) {
  unsigned int x = 193939393;
  s21_decimal y;
  ck_assert_int_eq(0, s21_from_int_to_decimal(x, &y));
}
END_TEST

Suite *s21_decimal_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_decimal");
  tc_core = tcase_create("Core");

  // michaleh
  tcase_add_test(tc_core, from_decimal_to_float);
  tcase_add_test(tc_core, from_decimal_to_float2);
  tcase_add_test(tc_core, from_decimal_to_int);
  tcase_add_test(tc_core, from_decimal_to_int2);
  tcase_add_test(tc_core, from_float_to_decimal);
  tcase_add_test(tc_core, from_float_to_decimal2);
  tcase_add_test(tc_core, from_float_to_decimal3);
  tcase_add_test(tc_core, from_int_to_decimal);
  tcase_add_test(tc_core, from_int_to_decimal2);
  tcase_add_test(tc_core, from_int_to_decimal3);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int no_failed;
  Suite *s;
  SRunner *sr;

  s = s21_decimal_test();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  no_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
