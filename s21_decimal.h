#ifndef SRC_SRC_DECIMAL_H_
#define SRC_SRC_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

enum error { OK = 0, ERROR };
enum sign { PLUS = 0, MINUS };
enum error error_status;
enum sign sign_bit;

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif
