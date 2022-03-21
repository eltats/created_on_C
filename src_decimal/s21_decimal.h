#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  s21_NORMAL_VALUE = 0,
  s21_INFINITY,
  s21_NEGATIVE_INFINITY,
  s21_NAN
} value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} s21_decimal;

typedef struct {
    unsigned int bits[7];
    value_type_t value_type;
} s21_super_decimal;


// main functions
s21_decimal s21_add(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_sub(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_mul(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_div(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_mod(s21_decimal first_num, s21_decimal second_num);
int s21_is_less(s21_decimal first_num, s21_decimal second_num);
int s21_is_less_or_equal(s21_decimal first_num, s21_decimal second_num);
int s21_is_greater(s21_decimal first_num, s21_decimal second_num);
int s21_is_greater_or_equal(s21_decimal first_num, s21_decimal second_num);
int s21_is_equal(s21_decimal first_num, s21_decimal second_num);
int s21_is_not_equal(s21_decimal first_num, s21_decimal second_num);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
s21_decimal s21_floor(s21_decimal number);
s21_decimal s21_round(s21_decimal number);
s21_decimal s21_truncate(s21_decimal number);
s21_decimal s21_negate(s21_decimal number);

// help functions
s21_decimal s21_init_decimal(unsigned int low_bits, unsigned int middle_bits,
                             unsigned int high_bits, unsigned int ss_bits,
                             int type);
int s21_is_less_int(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_binary_shift(s21_decimal number, int shift);
void s21_binary_print(s21_decimal number);
int s21_get_bit(s21_decimal number, int index);
void s21_set_bit(s21_decimal *number, int index, int bit);
s21_decimal s21_int_div_or_mod(s21_decimal first_num, s21_decimal second_num, int choose);
unsigned int s21_get_scale(s21_decimal number);
void s21_set_scale(s21_decimal *number, int scale);
void s21_erase_zero(s21_decimal *number, int temp_scale);
s21_decimal s21_get_whole_or_fraction(s21_decimal number, int choose);
s21_decimal s21_add_int(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_sub_int(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_mul_int(s21_decimal first_num, s21_decimal second_num);
s21_decimal s21_abs(s21_decimal number);
s21_decimal s21_ten_exp_scale(int scale);
void s21_difference_scales(s21_decimal *first_num, s21_decimal *second_num);
unsigned int s21_get_float_sign(const float num);
int s21_get_float_exp(float *exp);

// super decimal funcs
s21_super_decimal s21_super_add(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_sub(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_mul(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_div(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_mod(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_sub_int(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_add_int(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_mul_int(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_div_int_or_mod_int(s21_super_decimal first_num,
                                               s21_super_decimal second_num, int choose);
s21_super_decimal s21_super_mod_int(s21_super_decimal first_num, s21_super_decimal second_num);
int s21_super_is_less_int(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_init_decimal(unsigned int fstb, unsigned int scb,
                                         unsigned int tb, unsigned int frb, unsigned int fvb,
                                         unsigned int sxb, unsigned int svb, int type);
s21_super_decimal s21_super_binary_shift(s21_super_decimal number, int shift);
s21_super_decimal s21_super_right_binary_shift(s21_super_decimal number, int shift);
void s21_super_binary_print(s21_super_decimal number);
int s21_super_get_bit(s21_super_decimal number, int index);
void s21_super_set_bit(s21_super_decimal *number, int index, int bit);
s21_super_decimal s21_super_int_div_or_mod(s21_super_decimal first_num,
                                           s21_super_decimal second_num, int choose);
unsigned int s21_super_get_scale(s21_super_decimal number);
void s21_super_set_scale(s21_super_decimal *number, int scale);
int s21_super_get_high_bit(s21_super_decimal number);
s21_super_decimal s21_super_get_whole_or_fraction(s21_super_decimal number, int choose);
s21_super_decimal s21_super_abs(s21_super_decimal number);
s21_super_decimal s21_super_ten_exp_scale(int scale);
void s21_super_difference_scales(s21_super_decimal *first_num, s21_super_decimal *second_num);
void s21_super_div_mul_ten(s21_super_decimal *first_num, s21_super_decimal *second_num);
void s21_super_erase_zero(s21_super_decimal *number, int temp_scale);
int s21_super_is_less(s21_super_decimal first_num, s21_super_decimal second_num);
int s21_super_is_less_or_equal(s21_super_decimal first_num, s21_super_decimal second_num);
int s21_super_is_greater(s21_super_decimal first_num, s21_super_decimal second_num);
int s21_super_is_greater_or_equal(s21_super_decimal first_num, s21_super_decimal second_num);
int s21_super_is_equal(s21_super_decimal first_num, s21_super_decimal second_num);
int s21_super_is_not_equal(s21_super_decimal first_num, s21_super_decimal second_num);
s21_super_decimal s21_super_negate(s21_super_decimal number);
s21_super_decimal s21_super_greater_sub_lower(s21_super_decimal first_num, s21_super_decimal second_num);
#endif  // SRC_S21_DECIMAL_H_
