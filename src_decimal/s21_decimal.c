#include "s21_decimal.h"

s21_decimal s21_normalize(s21_super_decimal number) {
    s21_decimal result;
    s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    int scale = s21_super_get_scale(number);
    int sign = s21_super_get_bit(number, 223) == 0 ? 0 : 1;
    s21_super_set_bit(&number, 223, 0);
    int stop = 0;
    s21_super_decimal remainder = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal five = s21_super_init_decimal(5, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal one = s21_super_init_decimal(1, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    while (!stop) {
        if (scale < 0) {
            result = s21_init_decimal(0, 0, 0, 0, (sign) ? s21_NEGATIVE_INFINITY : s21_INFINITY);
            stop = 1;
        } else if (scale < 29 && number.bits[5] == 0 && number.bits[4] == 0 && number.bits[3] == 0) {
            if (!s21_super_is_greater_or_equal(remainder, five)) {
                if (s21_super_add_int(number, one).bits[3] == 0) {
                    number = s21_super_add_int(number, one);
                    result = s21_init_decimal(number.bits[0],
                                              number.bits[1], number.bits[2], 0, s21_NORMAL_VALUE);
                    s21_set_scale(&result, scale);
                    stop = 1;
                }
            } else {
                result = s21_init_decimal(number.bits[0], number.bits[1],
                                          number.bits[2], 0, s21_NORMAL_VALUE);
                s21_set_scale(&result, scale);
                stop = 1;
            }
        } else {
            remainder = s21_super_int_div_or_mod(number, ten, 0);
            number = s21_super_int_div_or_mod(number, ten, 1);
            scale--;
        }
    }
    s21_set_bit(&result, 127, sign);
    return result;
}

s21_decimal checkAdd(s21_decimal first, s21_decimal second) {
    s21_decimal result = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    if (first.value_type == s21_NAN || second.value_type == s21_NAN) {
        result.value_type = s21_NAN;
    } else if ((first.value_type == s21_INFINITY &&
                second.value_type == s21_NEGATIVE_INFINITY) ||
               (first.value_type == s21_NEGATIVE_INFINITY &&
                second.value_type == s21_INFINITY)) {
        result.value_type = s21_NAN;
    } else if (first.value_type == s21_INFINITY ||
               second.value_type == s21_INFINITY) {
        result.value_type = s21_INFINITY;
    } else if (first.value_type == s21_NEGATIVE_INFINITY ||
               second.value_type == s21_NEGATIVE_INFINITY) {
        result.value_type = s21_NEGATIVE_INFINITY;
    }
    return result;
}

s21_decimal checkSub(s21_decimal first, s21_decimal second) {
    s21_decimal result = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    if (first.value_type == s21_NAN || second.value_type == s21_NAN) {
        result.value_type = s21_NAN;
    } else if ((first.value_type == s21_INFINITY &&
                second.value_type == s21_INFINITY) ||
               (first.value_type == s21_NEGATIVE_INFINITY &&
                second.value_type == s21_NEGATIVE_INFINITY)) {
        result.value_type = s21_NAN;
    } else if (first.value_type == s21_INFINITY ||
               second.value_type == s21_NEGATIVE_INFINITY) {
        result.value_type = s21_INFINITY;
    } else if (first.value_type == s21_NEGATIVE_INFINITY ||
               second.value_type == s21_INFINITY) {
        result.value_type = s21_NEGATIVE_INFINITY;
    }
    return result;
}

s21_decimal checkMul(s21_decimal first, s21_decimal second) {
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_decimal result = zero;
    int fsign = (s21_get_bit(first, 127) == 0) ? 0 : 1;
    int ssign = (s21_get_bit(second, 127) == 0) ? 0 : 1;
    if (first.value_type == s21_NAN || second.value_type == s21_NAN) {
        result.value_type = s21_NAN;
    } else if ((!s21_is_equal(first, zero) && second.value_type != s21_NORMAL_VALUE) ||
               (!s21_is_equal(second, zero) && first.value_type != s21_NORMAL_VALUE)) {
        result.value_type = s21_NAN;
    } else if ((first.value_type == s21_INFINITY &&
                second.value_type == s21_NEGATIVE_INFINITY) ||
               (first.value_type == s21_NEGATIVE_INFINITY &&
                second.value_type == s21_INFINITY)) {
        result.value_type = s21_NEGATIVE_INFINITY;
    } else if ((first.value_type == s21_INFINITY &&
                second.value_type == s21_INFINITY) ||
               (first.value_type == s21_NEGATIVE_INFINITY &&
                second.value_type == s21_NEGATIVE_INFINITY)) {
        result.value_type = s21_INFINITY;
    } else if (first.value_type == s21_INFINITY) {
        result.value_type = 1 + ssign;
    } else if (first.value_type == s21_NEGATIVE_INFINITY) {
        result.value_type = 2 - ssign;
    } else if (second.value_type == s21_INFINITY) {
        result.value_type = 1 + fsign;
    } else if (second.value_type == s21_NEGATIVE_INFINITY) {
        result.value_type = 2 - fsign;
    }
    return result;
}

s21_decimal checkDiv(s21_decimal first, s21_decimal second) {
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_decimal result = zero;
    int fsign = (s21_get_bit(first, 127) == 0) ? 0 : 1;
    int ssign = (s21_get_bit(second, 127) == 0) ? 0 : 1;
    if (first.value_type == s21_NAN || second.value_type == s21_NAN) {
        result.value_type = s21_NAN;
    } else if ((first.value_type == s21_INFINITY ||
                first.value_type == s21_NEGATIVE_INFINITY) &&
               (second.value_type == s21_NEGATIVE_INFINITY ||
                second.value_type == s21_INFINITY)) {
        result.value_type = s21_NAN;
    } else if ((first.value_type == s21_INFINITY ||
                first.value_type == s21_NEGATIVE_INFINITY) &&
               !s21_is_equal(second, zero)) {
        result.value_type = s21_NAN;
    } else if (first.value_type == s21_INFINITY) {
        result.value_type = 1 + ssign;
    } else if (first.value_type == s21_NEGATIVE_INFINITY) {
        result.value_type = 2 - ssign;
    } else if (second.value_type == s21_INFINITY || second.value_type == s21_NEGATIVE_INFINITY) {
        result = zero;
    } else if (!s21_is_equal(first, zero) && !s21_is_equal(second, zero)) {
        result.value_type = s21_NAN;
    } else if (!s21_is_equal(second, zero)) {
        result.value_type = 1 + fsign;
    }
    return result;
}

s21_decimal checkMod(s21_decimal first, s21_decimal second) {
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_decimal result = zero;
    if (first.value_type == s21_NAN || second.value_type == s21_NAN) {
        result.value_type = s21_NAN;
    } else if ((first.value_type == s21_INFINITY ||
                first.value_type == s21_NEGATIVE_INFINITY) &&
               (second.value_type == s21_NEGATIVE_INFINITY ||
                second.value_type == s21_INFINITY)) {
        result.value_type = s21_NAN;
    } else if (!s21_is_equal(second, zero)) {
        result.value_type = s21_NAN;
    } else if (first.value_type == s21_INFINITY) {
        result.value_type = s21_INFINITY;
    } else if (first.value_type == s21_NEGATIVE_INFINITY) {
        result.value_type = s21_NEGATIVE_INFINITY;
    } else if (second.value_type == s21_NEGATIVE_INFINITY ||
               second.value_type == s21_INFINITY) {
        result = first;
    }
    return result;
}

// main functions
s21_decimal s21_add(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = checkAdd(first_num, second_num);
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    if (!s21_is_equal(result, zero)) {
        s21_super_decimal f = s21_super_init_decimal(first_num.bits[0],
                first_num.bits[1], first_num.bits[2], 0, 0, 0, first_num.bits[3], first_num.value_type);
        s21_super_decimal s = s21_super_init_decimal(second_num.bits[0],
                second_num.bits[1], second_num.bits[2], 0, 0, 0, second_num.bits[3], second_num.value_type);
        s21_super_decimal r = s21_super_add(f, s);
        result = s21_normalize(r);
    }
    return result;
}
s21_decimal s21_sub(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = checkSub(first_num, second_num);
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    if (!s21_is_equal(result, zero)) {
        s21_super_decimal f = s21_super_init_decimal(first_num.bits[0],
            first_num.bits[1], first_num.bits[2], 0, 0, 0, first_num.bits[3], first_num.value_type);
        s21_super_decimal s = s21_super_init_decimal(second_num.bits[0],
            second_num.bits[1], second_num.bits[2], 0, 0, 0, second_num.bits[3], second_num.value_type);
        s21_super_decimal r = s21_super_sub(f, s);
        result = s21_normalize(r);
    }
    return result;
}
s21_decimal s21_mul(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = checkMul(first_num, second_num);
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    if (!s21_is_equal(result, zero)) {
        s21_super_decimal f = s21_super_init_decimal(first_num.bits[0],
            first_num.bits[1], first_num.bits[2], 0, 0, 0, first_num.bits[3], first_num.value_type);
        s21_super_decimal s = s21_super_init_decimal(second_num.bits[0],
            second_num.bits[1], second_num.bits[2], 0, 0, 0, second_num.bits[3], second_num.value_type);
        s21_super_decimal r = s21_super_mul(f, s);
        result = s21_normalize(r);
    }
    return result;
}
s21_decimal s21_div(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = checkDiv(first_num, second_num);
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    if (!s21_is_equal(result, zero)) {
        s21_super_decimal f = s21_super_init_decimal(first_num.bits[0],
            first_num.bits[1], first_num.bits[2], 0, 0, 0, first_num.bits[3], first_num.value_type);
        s21_super_decimal s = s21_super_init_decimal(second_num.bits[0],
            second_num.bits[1], second_num.bits[2], 0, 0, 0, second_num.bits[3], second_num.value_type);
        s21_super_decimal r = s21_super_div(f, s);
        result = s21_normalize(r);
        s21_erase_zero(&result, 0);
    }
    return result;
}
s21_decimal s21_mod(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = checkMod(first_num, second_num);
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    if (!s21_is_equal(result, zero)) {
        s21_super_decimal f = s21_super_init_decimal(first_num.bits[0],
            first_num.bits[1], first_num.bits[2], 0, 0, 0, first_num.bits[3], first_num.value_type);
        s21_super_decimal s = s21_super_init_decimal(second_num.bits[0],
            second_num.bits[1], second_num.bits[2], 0, 0, 0, second_num.bits[3], second_num.value_type);
        s21_super_decimal r = s21_super_mod(f, s);
        result = s21_normalize(r);
    }
    return result;
}

int s21_compare_decimal_nan(s21_decimal first, s21_decimal second) {
    return first.value_type != s21_NAN && second.value_type != s21_NAN;
}
int s21_is_less(s21_decimal first_num, s21_decimal second_num) {
    int result = 1;
    if (s21_compare_decimal_nan(first_num, second_num)) {
        if (first_num.value_type == s21_NEGATIVE_INFINITY &&
            second_num.value_type != s21_NEGATIVE_INFINITY) {
            result = 0;
        } else if (second_num.value_type == s21_INFINITY &&
                   first_num.value_type != s21_INFINITY) {
            result = 0;
        } else if (first_num.value_type == s21_NORMAL_VALUE &&
                   second_num.value_type == s21_NORMAL_VALUE) {
            int first_scale = s21_get_scale(first_num);
            int second_scale = s21_get_scale(second_num);
            if (first_scale != 0 || second_scale != 0) {
                s21_decimal temp_first = s21_get_whole_or_fraction(first_num, 1);
                s21_decimal temp_second = s21_get_whole_or_fraction(second_num, 1);
                result = s21_is_equal(temp_first, temp_second);
                if (!result) {
                    temp_first = s21_get_whole_or_fraction(first_num, 0);
                    temp_second = s21_get_whole_or_fraction(second_num, 0);
                    s21_difference_scales(&temp_first, &temp_second);
                    result = s21_is_less_int(temp_first, temp_second);
                } else {
                result = s21_is_less_int(temp_first, temp_second);
                }
            } else {
                result = s21_is_less_int(first_num, second_num);
            }
        }
    }
    return result;
}

int s21_is_less_or_equal(s21_decimal first_num, s21_decimal second_num) {
    int result = 1;
    if (s21_compare_decimal_nan(first_num, second_num))
        if (!s21_is_less(first_num, second_num) || !s21_is_equal(first_num, second_num)) result = 0;
    return result;
}
int s21_is_greater(s21_decimal first_num, s21_decimal second_num) {
    int result = 1;
    if (s21_compare_decimal_nan(first_num, second_num))
        if (s21_is_less_or_equal(first_num, second_num)) result = 0;
    return result;
}
int s21_is_greater_or_equal(s21_decimal first_num, s21_decimal second_num) {
    int result = 1;
    if (s21_compare_decimal_nan(first_num, second_num))
        if (s21_is_less(first_num, second_num)) result = 0;
    return result;
}
int s21_is_equal(s21_decimal first_num, s21_decimal second_num) {
    int result = 0;
    if (!s21_compare_decimal_nan(first_num, second_num) ||
        (first_num.value_type == s21_INFINITY &&
         second_num.value_type != s21_INFINITY) ||
        (first_num.value_type != s21_INFINITY &&
         second_num.value_type == s21_INFINITY) ||
        (first_num.value_type == s21_NEGATIVE_INFINITY
         && second_num.value_type != s21_NEGATIVE_INFINITY) ||
        (first_num.value_type != s21_NEGATIVE_INFINITY
         && second_num.value_type == s21_NEGATIVE_INFINITY)) {
        result = 1;
    } else if (first_num.value_type == s21_NORMAL_VALUE && second_num.value_type == s21_NORMAL_VALUE) {
        if (first_num.bits[3] & 1u << 31) {
            if (second_num.bits[3] & 1u << 31) {
                for (int i = 2; i >= 0 && !result; i--) {
                    if (first_num.bits[i] != second_num.bits[i]) result = 1;
                }
            } else {
                for (int i = 2; i >= 0 && !result; i--) {
                    if ((first_num.bits[i] + second_num.bits[i]) != 0 ) result = 1;
                }
            }
        } else {
            if (second_num.bits[3] ^ (1u << 31)) {
                for (int i = 2; i >= 0 && !result; i--) {
                    if (first_num.bits[i] != second_num.bits[i]) result = 1;
                }
            } else {
                for (int i = 2; i >= 0 && !result; i--) {
                    if ((first_num.bits[i] + second_num.bits[i]) != 0 ) result = 1;
                }
            }
        }
        result = (s21_get_scale(first_num) == s21_get_scale(second_num)) ? result : 1;
    }
    return result;
}
int s21_is_not_equal(s21_decimal first_num, s21_decimal second_num) {
    int result = 1;
    if (s21_compare_decimal_nan(first_num, second_num))
        if (s21_is_equal(first_num, second_num)) result = 0;
    return result;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int result = 1;
    int sign = 0;
    if (src < 0) {
        sign = 1;
        src *= -1;
    }
    *dst = s21_init_decimal(src, 0, 0, 0, s21_NORMAL_VALUE);
    s21_set_bit(dst, 127, sign);
    result = 0;
    return result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int success = 1;
    if (src != src) {
        *dst = s21_init_decimal(0, 0, 0, 0, s21_NAN);
    } else if (src == 1.0 / 0.0) {
        *dst = s21_init_decimal(0, 0, 0, 0, s21_INFINITY);
    } else if (src == -1.0 / 0.0) {
        *dst = s21_init_decimal(0, 0, 0, 0, s21_NEGATIVE_INFINITY);
    } else {
        int sign = 0;
        if (src < 0.0L) {
            sign = 1;
            src *= -1;
        }
        double cast = (double)src;
        int power = 0;
        while ((int)truncl(cast) != 0) {
            cast /= 10.0;
            power++;
        }
        s21_decimal ten = s21_init_decimal(10, 0, 0, 0, s21_NORMAL_VALUE);
        s21_decimal one = s21_init_decimal(1, 0, 0, 0, s21_NORMAL_VALUE);
        s21_decimal temp;
        for (int i = 0; i < 7; i++) {
            *dst = s21_mul_int(*dst, ten);
            cast *= 10;
            double tmp = truncl(cast);
            s21_from_int_to_decimal((int)tmp, &temp);
            *dst = s21_add_int(*dst, temp);
            cast -= (int)tmp;
        }
        cast *= 10;
        cast = truncl(cast);
        if (cast >= 5.0L)
            *dst = s21_add_int(*dst, one);
        s21_set_scale(dst, 7 - power);
        s21_set_bit(dst, 127, sign);
        s21_erase_zero(dst, 0);
        success = 0;
    }
    return success;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int result = 1;
    if (src.value_type == s21_NORMAL_VALUE) {
        int sign = (src.bits[3] & (1u << 31)) ? 1 : 0;
        int scale = s21_get_scale(src);
        if (scale >= 0 && scale < 29) {
            src = s21_truncate(src);
            if (!src.bits[1] && !src.bits[2]) {
                *dst = src.bits[0];
                if (sign) *dst *= -1;
                result = 0;
            }
        }
    }
    return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int result = 0;
    if (src.value_type != 0) {
        result = 1;
    } else {
        int sign = (s21_get_bit(src, 127) == 0) ? 1 : -1;
        int scale = s21_get_scale(src);
        long double flo = 0;
        for (int i = 0; i < 96; ++i) {
            int one = (s21_get_bit(src, i) == 0) ? 0 : 1;
            flo += powl(2, i) * one;
        }
        *dst = flo * sign / pow(10, scale);
    }
    return result;
}

s21_decimal s21_floor(s21_decimal number) {
    if (number.value_type == s21_NORMAL_VALUE) {
        s21_decimal one = s21_init_decimal(1, 0, 0, 0, s21_NORMAL_VALUE);
        s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
        s21_decimal remaind;
        int sign = (s21_get_bit(number, 127) == 0) ? 0 : 1;
        s21_set_bit(&number, 127, 0);
        int scale = s21_get_scale(number);
        remaind = s21_get_whole_or_fraction(number, 0);
        s21_set_scale(&remaind, 0);
        number = s21_get_whole_or_fraction(number, 1);
        if (sign == 1) {
            if (scale != 0 && !s21_is_not_equal(remaind, zero)) {
                number = s21_add_int(number, one);
            }
            s21_set_bit(&number, 127, 1);
        }
    } else {
        number = s21_init_decimal(0, 0, 0, 0, number.value_type);
    }
    return number;
}
s21_decimal s21_round(s21_decimal number) {
    if (number.value_type == s21_NORMAL_VALUE) {
        s21_decimal one = s21_init_decimal(1, 0, 0, 0, s21_NORMAL_VALUE);
        s21_decimal five = s21_init_decimal(5, 0, 0, 0, s21_NORMAL_VALUE);
        s21_set_scale(&five, 1);
        s21_decimal remaind;
        int sign = (s21_get_bit(number, 127) == 0) ? 0 : 1;
        s21_set_bit(&number, 127, 0);
        remaind = s21_get_whole_or_fraction(number, 0);
        number = s21_get_whole_or_fraction(number, 1);
        if (!s21_is_greater_or_equal(remaind, five)) {
            number = s21_add_int(number, one);
            if (sign != 0) {
                s21_set_bit(&number, 127, 1);
            }
        }
    } else {
        number = s21_init_decimal(0, 0, 0, 0, number.value_type);
    }
    return number;
}
s21_decimal s21_truncate(s21_decimal number) {
    if (number.value_type == s21_NORMAL_VALUE) {
        int sign = (s21_get_bit(number, 127) == 0) ? 0 : 1;
        s21_set_bit(&number, 127, 0);
        number = s21_get_whole_or_fraction(number, 1);
        if (sign != 0) {
            s21_set_bit(&number, 127, 1);
        }
    } else {
        number = s21_init_decimal(0, 0, 0, 0, number.value_type);
    }
    return number;
}

s21_decimal s21_negate(s21_decimal number) {
    if (number.value_type == s21_INFINITY) {
        number = s21_init_decimal(0, 0, 0, 0, s21_NEGATIVE_INFINITY);
    } else if (number.value_type == s21_NEGATIVE_INFINITY) {
        number = s21_init_decimal(0, 0, 0, 0, s21_INFINITY);
    } else if (number.value_type == s21_NORMAL_VALUE) {
        number.bits[3] ^= (1u << 31);
    } else {
        number = s21_init_decimal(0, 0, 0, 0, s21_NAN);
    }
    return number;
}

s21_super_decimal s21_super_add(s21_super_decimal first_num, s21_super_decimal second_num) {
    int first_sign = s21_super_get_bit(first_num, 223) != 0 ? 1 : 0;
    int second_sign = s21_super_get_bit(second_num, 223) != 0 ? 1 : 0;
    s21_super_decimal result;
    if (first_sign != second_sign) {
        if (first_sign) {
            result = s21_super_sub(second_num, s21_super_negate(first_num));
        } else {
            result = s21_super_sub(first_num, s21_super_negate(second_num));
        }
    } else {
        if (first_sign) {
            s21_super_set_bit(&first_num, 223, 0);
            s21_super_set_bit(&second_num, 223, 0);
        }
        int temp_scale;
        if (s21_super_get_scale(first_num) > s21_super_get_scale(second_num)) {
            temp_scale = s21_super_get_scale(first_num);
        } else {
            temp_scale = s21_super_get_scale(second_num);
        }
        s21_super_div_mul_ten(&first_num, &second_num);
        result = s21_super_add_int(first_num, second_num);
        if (result.value_type == s21_NAN && s21_super_get_scale(first_num)) {
            int scale = s21_super_get_scale(first_num) - 1;
            s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
            s21_super_decimal five = s21_super_init_decimal(5, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
            s21_super_decimal one = s21_super_init_decimal(1, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
            s21_super_decimal remainder = s21_super_int_div_or_mod(first_num, ten, 0);
            first_num = s21_super_int_div_or_mod(first_num, ten, 1);
            if (!s21_super_is_greater(remainder, five)) {
                first_num = s21_super_add_int(first_num, one);
            }
            remainder = s21_super_int_div_or_mod(second_num, ten, 0);
            second_num = s21_super_int_div_or_mod(second_num, ten, 1);
            if (!s21_super_is_greater(remainder, five)) {
                second_num = s21_super_add_int(second_num, one);
            }
            s21_super_set_scale(&first_num, scale);
            s21_super_set_scale(&second_num, scale);
            result = s21_super_add_int(first_num, second_num);
        }
        s21_super_set_scale(&result, s21_super_get_scale(first_num));
        s21_super_erase_zero(&result, temp_scale);
        if (first_sign) {
            result = s21_super_negate(result);
        }
    }
    return result;
}
s21_super_decimal s21_super_sub(s21_super_decimal first_num, s21_super_decimal second_num) {
    s21_super_decimal result;
    int first_sign = s21_super_get_bit(first_num, 223) != 0 ? 1 : 0;
    int second_sign = s21_super_get_bit(second_num, 223) != 0 ? 1 : 0;
    if (first_sign != second_sign) {
        result = s21_super_add(first_num, s21_super_negate(second_num));
    } else {
        int temp_scale;
        if (s21_super_get_scale(first_num) > s21_super_get_scale(second_num)) {
            temp_scale = s21_super_get_scale(first_num);
        } else {
            temp_scale = s21_super_get_scale(second_num);
        }
        s21_super_div_mul_ten(&first_num, &second_num);
        s21_super_set_bit(&first_num, 223, first_sign);
        s21_super_set_bit(&second_num, 223, second_sign);
        result = s21_super_sub_int(first_num, second_num);
        s21_super_set_scale(&result, s21_super_get_scale(first_num));
        s21_super_erase_zero(&result, temp_scale);
    }
    return result;
}
s21_super_decimal s21_super_mul(s21_super_decimal first_num, s21_super_decimal second_num) {
    int first_scale = s21_super_get_scale(first_num);
    int second_scale = s21_super_get_scale(second_num);
    s21_super_set_scale(&first_num, 0);
    s21_super_set_scale(&second_num, 0);
    s21_super_decimal result = s21_super_mul_int(first_num, second_num);
    s21_super_set_scale(&result, first_scale + second_scale);
    s21_super_erase_zero(&result, 0);
    return result;
}
s21_super_decimal s21_super_div(s21_super_decimal first_num, s21_super_decimal second_num) {
    s21_super_decimal result = s21_super_div_int_or_mod_int(first_num, second_num, 1);
    s21_super_decimal remainder = s21_super_div_int_or_mod_int(first_num, second_num, 0);
    s21_super_decimal temp;
    int res_scale = s21_super_get_scale(result);
    s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal five = s21_super_init_decimal(5, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal one = s21_super_init_decimal(1, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    int first_scale = s21_super_get_scale(first_num);
    int second_scale = s21_super_get_scale(second_num);
    int dif_scale = first_scale - second_scale;
    while (dif_scale < 0) {
        dif_scale++;
        if (s21_super_mul_int(result, ten).value_type == s21_NAN) {
            res_scale--;
        } else {
            result = s21_super_mul_int(result, ten);
            remainder = s21_super_mul_int(remainder, ten);
            temp = s21_super_int_div_or_mod(remainder, second_num, 1);
            result = s21_super_add_int(result, temp);
            remainder = s21_super_int_div_or_mod(remainder, second_num, 0);
        }
    }
    remainder = s21_super_mul_int(remainder, ten);
    temp = s21_super_int_div_or_mod(remainder, second_num, 1);
    if (!s21_super_is_greater_or_equal(temp, five)) {
        result = s21_super_add_int(result, one);
    }
    s21_super_set_scale(&result, res_scale);
    s21_super_erase_zero(&result, 0);
    return result;
}
s21_super_decimal s21_super_mod(s21_super_decimal first_num, s21_super_decimal second_num) {
    int first_scale = s21_super_get_scale(first_num);
    int second_scale = s21_super_get_scale(second_num);
    int res_scale;
    int sign = (s21_super_get_bit(first_num, 223) == 0) ? 0 : 1;
    s21_super_set_scale(&first_num, 0);
    s21_super_set_scale(&second_num, 0);
    s21_super_set_bit(&first_num, 223, 0);
    s21_super_set_bit(&second_num, 223, 0);
    if (first_scale < second_scale) {
        s21_super_decimal exp = s21_super_ten_exp_scale(second_scale - first_scale);
        first_num = s21_super_mul_int(first_num, exp);
        res_scale = second_scale;
    } else {
        s21_super_decimal exp = s21_super_ten_exp_scale(first_scale - second_scale);
        second_num = s21_super_mul_int(second_num, exp);
        res_scale = first_scale;
    }
    s21_super_decimal remainder = s21_super_int_div_or_mod(first_num, second_num, 0);
    s21_super_set_scale(&remainder, res_scale);
    s21_super_set_bit(&remainder, 223, sign);
    s21_super_erase_zero(&remainder, res_scale);
    return remainder;
}

s21_super_decimal s21_super_sub_int(s21_super_decimal first_num, s21_super_decimal second_num) {
    s21_super_decimal result;
    if (first_num.bits[6] & (1u << 31)) {
        if (second_num.bits[6] & (1u << 31)) {
            first_num = s21_super_negate(first_num);
            second_num = s21_super_negate(second_num);
            if (!s21_super_is_greater(first_num, second_num)) {
                result = s21_super_greater_sub_lower(first_num, second_num);
                result = s21_super_negate(result);
            } else {
                result = s21_super_greater_sub_lower(second_num, first_num);
            }
        } else {
            first_num = s21_super_negate(first_num);
            result = s21_super_add_int(first_num, second_num);
            result = s21_super_negate(result);
        }
    } else {
        if (second_num.bits[6] & (1u << 31)) {
            second_num = s21_super_negate(second_num);
            result = s21_super_add_int(first_num, second_num);
        } else {
            if (!s21_super_is_greater(first_num, second_num)) {
                result = s21_super_greater_sub_lower(first_num, second_num);
            } else {
                result = s21_super_greater_sub_lower(second_num, first_num);
                result = s21_super_negate(result);
            }
        }
    }
    return result;
}
s21_super_decimal s21_super_add_int(s21_super_decimal first_num, s21_super_decimal second_num) {
    s21_super_decimal result = first_num;
    if (first_num.value_type == s21_NAN || second_num.value_type == s21_NAN) {
        result = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NAN);
    } else {
        int negative = 0;
        if (first_num.bits[6] & (1u << 31)) {
            negative++;
        }
        s21_super_decimal temp = second_num;
        s21_super_decimal zero = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
        if ((first_num.bits[6] & (1u << 31)) == (second_num.bits[6] & (1u << 31))) {
            while (s21_super_is_equal(temp, zero)) {
                first_num = result;
                second_num = temp;
                temp = zero;
                result = zero;
                for (int i = 0, stop = 0; i < 192 && !stop; i++) {
                    if (s21_super_get_bit(first_num, i) && s21_super_get_bit(second_num, i)) {
                        if (i == 191) {
                            result = zero;
                            result.value_type = s21_NAN;
                            temp = zero;
                            stop = 1;
                        } else {
                            s21_super_set_bit(&temp, i + 1, 1);
                        }
                    } else {
                        if (s21_super_get_bit(first_num, i) || s21_super_get_bit(second_num, i)) {
                            s21_super_set_bit(&result, i, 1);
                        }
                    }
                }
            }
            if (negative && result.value_type != s21_NAN) {
                result = s21_super_negate(result);
            }
        } else {
            result = s21_super_sub_int(first_num, s21_super_negate(second_num));
        }
    }
    return result;
}
s21_super_decimal s21_super_mul_int(s21_super_decimal first_num, s21_super_decimal second_num) {
    s21_super_decimal result = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal temp;
    int negative = 1;
    if ((first_num.bits[6] & (1u << 31)) == (second_num.bits[6] & (1u << 31))) {
        negative = 0;
    }
    first_num = s21_super_abs(first_num);
    second_num = s21_super_abs(second_num);
    temp = first_num;
    for (int i = 0, stop = 0; i < 192 && !stop; i++) {
        if (s21_super_get_bit(second_num, i)) {
            result = s21_super_add_int(result, temp);
            if (result.value_type == s21_NAN || temp.value_type == s21_NAN) {
                result = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NAN);
                stop = 1;
            }
        }
        temp = s21_super_binary_shift(temp, 1);
    }
    if (result.value_type != s21_NAN) {
        if (negative) {
            result = s21_super_negate(result);
        }
    }
    return result;
}
s21_super_decimal s21_super_div_int_or_mod_int(s21_super_decimal first_num,
                                               s21_super_decimal second_num, int choose) {
    int temp_scale = 0;
    int dif_scale = s21_super_get_scale(first_num) - s21_super_get_scale(second_num);
    s21_super_decimal result = s21_super_int_div_or_mod(first_num, second_num, 1);
    s21_super_decimal zero = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal remainder = zero;
    s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal one = s21_super_init_decimal(1, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal five = s21_super_init_decimal(5, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal temp = s21_super_int_div_or_mod(first_num, second_num, 0);
    while (!s21_super_is_not_equal(temp, zero) && temp_scale < 28 - dif_scale) {
        s21_super_decimal whole;
        temp = s21_super_mul_int(temp, ten);
        whole = s21_super_int_div_or_mod(temp, second_num, 1);
        temp = s21_super_int_div_or_mod(temp, second_num, 0);
        remainder = temp;
        if (s21_super_mul_int(result, ten).value_type == s21_NORMAL_VALUE) {
            result = s21_super_mul_int(result, ten);
            temp_scale++;
            result = s21_super_add_int(result, whole);
        } else {
            if (!s21_super_is_greater_or_equal(whole, five))
                result = s21_super_add_int(result, one);
            temp = zero;
        }
    }
    temp_scale += (dif_scale < 0) ? 0 : dif_scale;
    if (temp_scale >= 0) {
        s21_super_set_scale(&result, temp_scale);
    } else {
        temp_scale = abs(temp_scale);
        for (int i = 0; i < temp_scale; i++) {
            result = s21_super_mul_int(result, ten);
        }
    }
    return (choose == 1) ? result : remainder;
}
int s21_super_is_less_int(s21_super_decimal first_num, s21_super_decimal second_num) {
    int result = 1;
    if (first_num.bits[6] & (1u << 31)) {
        if (second_num.bits[6] & 1u << 31) {
            for (int i = 5, stop = 0; i >= 0 && !stop; i--) {
                if (first_num.bits[i] > second_num.bits[i]) {
                    result = 0;
                    stop = 1;
                } else if (first_num.bits[i] < second_num.bits[i]) {
                    stop = 1;
                } else {}
            }
        } else {
            for (int i = 5, stop = 0; i >= 0 && !stop; i--) {
                if (first_num.bits[i] + second_num.bits[i] != 0) {
                    result = 0;
                    stop = 1;
                }
            }
        }
    } else {
        if (second_num.bits[6] ^ (1u << 31)) {
            for (int i = 5, stop = 0; i >= 0 && !stop; i--) {
                if (first_num.bits[i] < second_num.bits[i]) {
                    result = 0;
                    stop = 1;
                } else if (first_num.bits[i] > second_num.bits[i]) {
                    stop = 1;
                } else {}
            }
        }
    }
    return result;
}
s21_super_decimal s21_super_init_decimal(unsigned int fstb,
                                         unsigned int scb,
                                         unsigned int tb,
                                         unsigned int frb,
                                         unsigned int fvb,
                                         unsigned int sxb,
                                         unsigned int svb,
                                         int type) {
    s21_super_decimal result;
    result.bits[0] = fstb;
    result.bits[1] = scb;
    result.bits[2] = tb;
    result.bits[3] = frb;
    result.bits[4] = fvb;
    result.bits[5] = sxb;
    result.bits[6] = svb;
    result.value_type = type;
    return result;
}
s21_super_decimal s21_super_binary_shift(s21_super_decimal number, int shift) {
    s21_super_decimal result = number;
    if (result.value_type != s21_NAN) {
        s21_super_decimal temp;
        for (int j = 0, stop = 0; j < shift && !stop; j++) {
            temp = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
            for (int i = 0; i < 192 && !stop; i++) {
                if (s21_super_get_bit(result, i)) {
                    if (i == 191) {
                        temp = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NAN);
                        stop = 1;
                    } else {
                        s21_super_set_bit(&temp, i + 1, 1);
                    }
                }
            }
            result = temp;
        }
    }
    return result;
}
s21_super_decimal s21_super_right_binary_shift(s21_super_decimal number, int shift) {
    s21_super_decimal result = number;
    s21_super_decimal temp;
    for (int j = 0, stop = 0; j < shift && !stop; j++) {
        temp = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
        for (int i = 191; i >= 0 && !stop; i--) {
            if (s21_super_get_bit(result, i)) {
                if (i == 0) {
                    temp = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NAN);
                    stop = 1;
                } else {
                    s21_super_set_bit(&temp, i - 1, 1);
                }
            }
        }
        result = temp;
    }
    return result;
}
int s21_super_get_bit(s21_super_decimal number, int index) {
    int mask = 1 << (index % 32);
    int result = number.bits[index / 32] & mask;
    return result;
}
void s21_super_set_bit(s21_super_decimal *number, int index, int bit) {
    int mask = 1 << (index % 32);
    mask = (bit) ? mask : ~mask;
    number->bits[index / 32] = (bit) ?
    number->bits[index / 32] | mask :
    number->bits[index / 32] & mask;
}
s21_super_decimal s21_super_int_div_or_mod(s21_super_decimal first_num,
                                           s21_super_decimal second_num, int choose) {
    s21_super_set_scale(&first_num, 0);
    s21_super_set_scale(&second_num, 0);
    s21_super_set_bit(&first_num, 223, 0);
    s21_super_set_bit(&second_num, 223, 0);
    s21_super_decimal result = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    int shift_count = 0;
    while (s21_super_binary_shift(second_num, 1).value_type != s21_NAN) {
        second_num = s21_super_binary_shift(second_num, 1);
        shift_count++;
    }
    while (shift_count >= 0) {
        if (!s21_super_is_greater_or_equal(first_num, second_num)) {
            first_num = s21_super_sub_int(first_num, second_num);
            s21_super_set_bit(&result, shift_count, 1);
        }
        second_num = s21_super_right_binary_shift(second_num, 1);
        shift_count--;
    }
    return (choose) ? result : first_num;
}
unsigned int s21_super_get_scale(s21_super_decimal number) {
    unsigned int result = number.bits[6];
    if (result & (1u << 31))
        result ^= (1u << 31);
    result >>= 16;
    result &= 63;
    return result;
}
void s21_super_set_scale(s21_super_decimal *number, int scale) {
    int sign = (number->bits[6] & (1u << 31)) ? 1 : 0;
    number->bits[6] = 0;
    scale <<= 16;
    number->bits[6] |= scale;
    s21_super_set_bit(number, 223, sign);
}
s21_super_decimal s21_super_get_whole_or_fraction(s21_super_decimal number, int choose) {
    int scale = s21_super_get_scale(number);
    int sign = s21_super_get_bit(number, 223) != 0 ? 1 : 0;
    s21_super_set_bit(&number, 223, 0);
    s21_super_decimal exp = s21_super_ten_exp_scale(scale);
    s21_super_decimal result = s21_super_int_div_or_mod(number, exp, choose);
    if (!choose) {
        s21_super_set_scale(&result, scale);
    }
    s21_super_set_bit(&result, 223, sign);
    return result;
}
s21_super_decimal s21_super_abs(s21_super_decimal number) {
    if (number.bits[6] & (1u << 31)) {
        number.bits[6] ^= (1u << 31);
    }
    return number;
}
s21_super_decimal s21_super_ten_exp_scale(int scale) {
    s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal exp = s21_super_init_decimal(1, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    while (scale-- != 0) {
        exp = s21_super_mul_int(ten, exp);
    }
    return exp;
}
void s21_super_difference_scales(s21_super_decimal *first_num, s21_super_decimal *second_num) {
    int first_scale = s21_super_get_scale(*first_num);
    int second_scale = s21_super_get_scale(*second_num);
    if ((first_scale > 0 || second_scale > 0) && (first_scale != second_scale)) {
        int scale = abs(first_scale - second_scale);
        s21_super_decimal exp = s21_super_ten_exp_scale(scale);
        if (first_scale < second_scale) {
            s21_super_set_scale(first_num, 0);
            *first_num = s21_super_mul_int(*first_num, exp);
        } else {
            s21_super_set_scale(second_num, 0);
            *second_num = s21_super_mul_int(*second_num, exp);
        }
    }
}

void s21_equal_scale(s21_super_decimal *first_num, s21_super_decimal *second_num, int scale, int res_scale) {
    s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal exp = s21_super_ten_exp_scale(scale);
    s21_super_decimal remainder = s21_super_int_div_or_mod(*first_num, exp, 0);
    s21_super_decimal five = s21_super_init_decimal(5, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal one = s21_super_init_decimal(1, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    if (s21_super_mul_int(remainder, ten).value_type == s21_NAN) {
        for (int i = 0; i < scale - 1; i++) {
            remainder = s21_super_int_div_or_mod(remainder, ten, 1);
        }
        remainder = s21_super_int_div_or_mod(remainder, ten, 0);
    }  else {
        remainder = s21_super_mul_int(remainder, ten);
        remainder = s21_super_int_div_or_mod(remainder, exp, 1);
    }
    *first_num = s21_super_int_div_or_mod(*first_num, exp, 1);
    if (!s21_super_is_greater_or_equal(remainder, five)) {
        *first_num = s21_super_add_int(*first_num, one);
    }
    s21_super_set_scale(first_num, res_scale);
    s21_super_set_scale(second_num, res_scale);
}
void s21_super_div_mul_ten(s21_super_decimal *first_num, s21_super_decimal *second_num) {
    int first_scale = s21_super_get_scale(*first_num);
    int second_scale = s21_super_get_scale(*second_num);
    if (first_scale != second_scale) {
        s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
        s21_super_set_scale(first_num, 0);
        s21_super_set_scale(second_num, 0);
        while (s21_super_mul_int(*first_num, ten).value_type != s21_NAN && first_scale < 57) {
            *first_num = s21_super_mul_int(*first_num, ten);
            first_scale++;
        }
        while (s21_super_mul_int(*second_num, ten).value_type != s21_NAN && second_scale < 57) {
            *second_num = s21_super_mul_int(*second_num, ten);
            second_scale++;
        }
        int scale = abs(first_scale - second_scale);
        if (first_scale > second_scale) {
            s21_equal_scale(first_num, second_num, scale, second_scale);
        } else {
            s21_equal_scale(second_num, first_num, scale, first_scale);
        }
    }
}
void s21_super_erase_zero(s21_super_decimal *number, int temp_scale) {
    s21_super_decimal zero = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_super_decimal ten = s21_super_init_decimal(10, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    int scale = s21_super_get_scale(*number);
    while (!s21_super_is_equal(s21_super_int_div_or_mod(*number, ten, 0), zero) && scale > temp_scale) {
        *number = s21_super_int_div_or_mod(*number, ten, 1);
        scale--;
    }
    if ((unsigned int)scale != s21_super_get_scale(*number))
        s21_super_set_scale(number, scale);
}
int s21_super_is_less(s21_super_decimal first_num, s21_super_decimal second_num) {
    int result = 1;
    int first_scale = s21_super_get_scale(first_num);
    int second_scale = s21_super_get_scale(second_num);
    if (first_scale != 0 || second_scale != 0) {
        s21_super_decimal temp_first = s21_super_get_whole_or_fraction(first_num, 1);
        s21_super_decimal temp_second = s21_super_get_whole_or_fraction(second_num, 1);
        result = s21_super_is_equal(temp_first, temp_second);
        if (!result) {
            temp_first = s21_super_get_whole_or_fraction(first_num, 0);
            temp_second = s21_super_get_whole_or_fraction(second_num, 0);
            s21_super_difference_scales(&temp_first, &temp_second);
            result = s21_super_is_less_int(temp_first, temp_second);
        } else {
            result = s21_super_is_less_int(temp_first, temp_second);
        }
    } else {
        result = s21_super_is_less_int(first_num, second_num);
    }
    return result;
}
int s21_super_is_less_or_equal(s21_super_decimal first_num, s21_super_decimal second_num) {
    int result = 1;
    if (!s21_super_is_less(first_num, second_num) || !s21_super_is_equal(first_num, second_num)) result = 0;
    return result;
}
int s21_super_is_greater(s21_super_decimal first_num, s21_super_decimal second_num) {
    int result = 1;
    if (s21_super_is_less_or_equal(first_num, second_num)) result = 0;
    return result;
}
int s21_super_is_greater_or_equal(s21_super_decimal first_num, s21_super_decimal second_num) {
    int result = 1;
    if (s21_super_is_less(first_num, second_num)) result = 0;
    return result;
}
int s21_super_is_equal(s21_super_decimal first_num, s21_super_decimal second_num) {
    int result = 0;
    if (first_num.bits[6] & 1u << 31) {
        if (second_num.bits[6] & 1u << 31) {
            for (int i = 5; i >= 0 && !result; i--) {
                if (first_num.bits[i] != second_num.bits[i]) result = 1;
            }
        } else {
            for (int i = 5; i >= 0 && !result; i--) {
                if ((first_num.bits[i] + second_num.bits[i]) != 0 ) result = 1;
            }
        }
    } else {
        if (second_num.bits[6] ^ (1u << 31)) {
            for (int i = 5; i >= 0 && !result; i--) {
                if (first_num.bits[i] != second_num.bits[i]) result = 1;
            }
        } else {
            for (int i = 5; i >= 0 && !result; i--) {
                if ((first_num.bits[i] + second_num.bits[i]) != 0 ) result = 1;
            }
        }
    }
    result = (s21_super_get_scale(first_num) == s21_super_get_scale(second_num)) ? result : 1;
    return result;
}
int s21_super_is_not_equal(s21_super_decimal first_num, s21_super_decimal second_num) {
    int result = 1;
    if (s21_super_is_equal(first_num, second_num)) result = 0;
    return result;
}
s21_super_decimal s21_super_negate(s21_super_decimal number) {
    number.bits[6] ^= (1u << 31);
    return number;
}
s21_super_decimal s21_super_greater_sub_lower(s21_super_decimal first_num, s21_super_decimal second_num) {
    s21_super_decimal result = first_num;
    s21_super_decimal temp = second_num;
    s21_super_decimal zero = s21_super_init_decimal(0, 0, 0, 0, 0, 0, 0, s21_NORMAL_VALUE);
    while (s21_super_is_equal(temp, zero)) {
        first_num = result;
        second_num = temp;
        temp = zero;
        result = zero;
        for (int i = 0; i < 192; i++) {
            if (s21_super_get_bit(first_num, i)) {
                if (!s21_super_get_bit(second_num, i)) {
                    s21_super_set_bit(&result, i, 1);
                }
            } else {
                if (s21_super_get_bit(second_num, i)) {
                    s21_super_set_bit(&temp, i + 1, 1);
                    s21_super_set_bit(&result, i, 1);
                }
            }
        }
    }
    return result;
}

// help functions
s21_decimal s21_greater_sub_lower(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = first_num;
    s21_decimal temp = second_num;
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    while (s21_is_equal(temp, zero)) {
        first_num = result;
        second_num = temp;
        temp = zero;
        result = zero;
        for (int i = 0; i < 96; i++) {
            if (s21_get_bit(first_num, i)) {
                if (!s21_get_bit(second_num, i)) {
                    s21_set_bit(&result, i, 1);
                }
            } else {
                if (s21_get_bit(second_num, i)) {
                    s21_set_bit(&temp, i + 1, 1);
                    s21_set_bit(&result, i, 1);
                }
            }
        }
    }
    return result;
}
s21_decimal s21_sub_int(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result;
    if (first_num.bits[3] & (1u << 31)) {
        if (second_num.bits[3] & (1u << 31)) {
            first_num = s21_negate(first_num);
            second_num = s21_negate(second_num);
            if (!s21_is_greater(first_num, second_num)) {
                result = s21_greater_sub_lower(first_num, second_num);
                result = s21_negate(result);
            } else {
                result = s21_greater_sub_lower(second_num, first_num);
            }
        } else {
            first_num = s21_negate(first_num);
            result = s21_add_int(first_num, second_num);
            result = s21_negate(result);
        }
    } else {
        if (second_num.bits[3] & (1u << 31)) {
            second_num = s21_negate(second_num);
            result = s21_add_int(first_num, second_num);
        } else {
            if (!s21_is_greater(first_num, second_num)) {
                result = s21_greater_sub_lower(first_num, second_num);
            } else {
                result = s21_greater_sub_lower(second_num, first_num);
                result = s21_negate(result);
            }
        }
    }
    return result;
}
s21_decimal s21_add_int(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = first_num;
    if (first_num.value_type == s21_NAN || second_num.value_type == s21_NAN) {
        result = s21_init_decimal(0, 0, 0, 0, s21_NAN);
    } else {
        int negative = 0;
        if (first_num.bits[3] & (1u << 31)) {
            negative++;
        }
        s21_decimal temp = second_num;
        s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
        if ((first_num.bits[3] & (1u << 31)) == (second_num.bits[3] & (1u << 31))) {
            while (s21_is_equal(temp, zero)) {
                first_num = result;
                second_num = temp;
                temp = zero;
                result = zero;
                for (int i = 0, stop = 0; i < 96 && !stop; i++) {
                    if (s21_get_bit(first_num, i) && s21_get_bit(second_num, i)) {
                        if (i == 95) {
                            result = zero;
                            result.value_type = s21_NAN;
                            temp = zero;
                            stop = 1;
                        } else {
                            s21_set_bit(&temp, i + 1, 1);
                        }
                    } else {
                        if (s21_get_bit(first_num, i) || s21_get_bit(second_num, i)) {
                            s21_set_bit(&result, i, 1);
                        }
                    }
                }
            }
            if (negative && result.value_type != s21_NAN) {
                result = s21_negate(result);
            }
        } else {
            result = s21_sub_int(first_num, s21_negate(second_num));
        }
    }
    return result;
}
s21_decimal s21_mul_int(s21_decimal first_num, s21_decimal second_num) {
    s21_decimal result = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_decimal temp;
    int negative = 1;
    if ((first_num.bits[3] & (1u << 31)) == (second_num.bits[3] & (1u << 31))) {
        negative = 0;
    }
    first_num = s21_abs(first_num);
    second_num = s21_abs(second_num);
    temp = first_num;
    for (int i = 0, stop = 0; i < 96 && !stop; i++) {
        if (s21_get_bit(second_num, i)) {
            result = s21_add_int(result, temp);
            if (result.value_type == s21_NAN || temp.value_type == s21_NAN) {
                result = s21_init_decimal(0, 0, 0, 0, s21_NAN);
                stop = 1;
            }
        }
        temp = s21_binary_shift(temp, 1);
    }
    if (result.value_type != s21_NAN) {
        if (negative) {
            result = s21_negate(result);
        }
    }
    return result;
}
int s21_is_less_int(s21_decimal first_num, s21_decimal second_num) {
    int result = 1;
    if (first_num.bits[3] & (1u << 31)) {
        if (second_num.bits[3] & 1u << 31) {
            for (int i = 2, stop = 0; i >= 0 && !stop; i--) {
                if (first_num.bits[i] > second_num.bits[i]) {
                    result = 0;
                    stop = 1;
                } else if (first_num.bits[i] < second_num.bits[i]) {
                    stop = 1;
                } else {}
            }
        } else {
            for (int i = 2, stop = 0; i >= 0 && !stop; i--) {
                if (first_num.bits[i] + second_num.bits[i] != 0) {
                    result = 0;
                    stop = 1;
                }
            }
        }
    } else {
        if (second_num.bits[3] ^ (1u << 31)) {
            for (int i = 2, stop = 0; i >= 0 && !stop; i--) {
                if (first_num.bits[i] < second_num.bits[i]) {
                    result = 0;
                    stop = 1;
                } else if (first_num.bits[i] > second_num.bits[i]) {
                    stop = 1;
                } else {}
            }
        }
    }
    return result;
}
s21_decimal s21_init_decimal(unsigned int low_bits,
                             unsigned int middle_bits,
                             unsigned int high_bits,
                             unsigned int ss_bits,
                             int type) {
    s21_decimal result;
    result.bits[0] = low_bits;
    result.bits[1] = middle_bits;
    result.bits[2] = high_bits;
    result.bits[3] = ss_bits;
    result.value_type = type;
    return result;
}
s21_decimal s21_binary_shift(s21_decimal number, int shift) {
    s21_decimal result = number;
    if (result.value_type != s21_NAN) {
        s21_decimal temp;
        for (int j = 0, stop = 0; j < shift && !stop; j++) {
            temp = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
            for (int i = 0; i < 96 && !stop; i++) {
                if (s21_get_bit(result, i)) {
                    if (i == 95) {
                        temp = s21_init_decimal(0, 0, 0, 0, s21_NAN);
                        stop = 1;
                    } else {
                        s21_set_bit(&temp, i + 1, 1);
                    }
                }
            }
            result = temp;
        }
    }
    return result;
}
s21_decimal s21_right_binary_shift(s21_decimal number, int shift) {
    s21_decimal result = number;
    s21_decimal temp;
    for (int j = 0, stop = 0; j < shift && !stop; j++) {
        temp = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
        for (int i = 95; i >= 0 && !stop; i--) {
            if (s21_get_bit(result, i)) {
                if (i == 0) {
                    temp = s21_init_decimal(0, 0, 0, 0, s21_NAN);
                    stop = 1;
                } else {
                    s21_set_bit(&temp, i - 1, 1);
                }
            }
        }
        result = temp;
    }
    return result;
}
int s21_get_bit(s21_decimal number, int index) {
    int mask = 1 << (index % 32);
    int result = number.bits[index / 32] & mask;
    return result;
}
void s21_set_bit(s21_decimal *number, int index, int bit) {
    int mask = 1 << (index % 32);
    mask = (bit) ? mask : ~mask;
    number->bits[index / 32] = (bit) ?
    number->bits[index / 32] | mask :
    number->bits[index / 32] & mask;
}
s21_decimal s21_int_div_or_mod(s21_decimal first_num, s21_decimal second_num, int choose) {
    s21_set_scale(&first_num, 0);
    s21_set_scale(&second_num, 0);
    s21_decimal result = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    int shift_count = 0;
    while (s21_binary_shift(second_num, 1).value_type != s21_NAN) {
        second_num = s21_binary_shift(second_num, 1);
        shift_count++;
    }
    while (shift_count >= 0) {
        if (!s21_is_greater_or_equal(first_num, second_num)) {
            first_num = s21_sub_int(first_num, second_num);
            s21_set_bit(&result, shift_count, 1);
        }
        second_num = s21_right_binary_shift(second_num, 1);
        shift_count--;
    }
    return (choose) ? result : first_num;
}
unsigned int s21_get_scale(s21_decimal number) {
    unsigned int result = number.bits[3];
    if (result & (1u << 31))
        result ^= (1u << 31);
    result >>= 16;
    result &= 31;
    return result;
}
void s21_set_scale(s21_decimal *number, int scale) {
    int sign = (number->bits[3] & (1u << 31)) ? 1 : 0;
    number->bits[3] = 0;
    scale <<= 16;
    number->bits[3] |= scale;
    s21_set_bit(number, 127, sign);
}
s21_decimal s21_get_whole_or_fraction(s21_decimal number, int choose) {
    int scale = s21_get_scale(number);
    int sign = s21_get_bit(number, 127) != 0 ? 1 : 0;
    s21_set_bit(&number, 127, 0);
    s21_decimal exp = s21_ten_exp_scale(scale);
    s21_decimal result = s21_int_div_or_mod(number, exp, choose);
    if (!choose) {
        s21_set_scale(&result, scale);
    }
    s21_set_bit(&result, 127, sign);
    return result;
}
s21_decimal s21_abs(s21_decimal number) {
    if (number.bits[3] & (1u << 31)) {
        number.bits[3] ^= (1u << 31);
    }
    return number;
}
s21_decimal s21_ten_exp_scale(int scale) {
    s21_decimal ten = s21_init_decimal(10, 0, 0, 0, s21_NORMAL_VALUE);
    s21_decimal exp = s21_init_decimal(1, 0, 0, 0, s21_NORMAL_VALUE);
    while (scale-- != 0) {
        exp = s21_mul_int(ten, exp);
    }
    return exp;
}
void s21_difference_scales(s21_decimal *first_num, s21_decimal *second_num) {
    int first_scale = s21_get_scale(*first_num);
    int second_scale = s21_get_scale(*second_num);
    if ((first_scale > 0 || second_scale > 0) && (first_scale != second_scale)) {
        int scale = abs(first_scale - second_scale);
        s21_decimal exp = s21_ten_exp_scale(scale);
        if (first_scale < second_scale) {
            s21_set_scale(first_num, 0);
            *first_num = s21_mul_int(*first_num, exp);
        } else {
            s21_set_scale(second_num, 0);
            *second_num = s21_mul_int(*second_num, exp);
        }
    }
}
void s21_erase_zero(s21_decimal *number, int temp_scale) {
    s21_decimal zero = s21_init_decimal(0, 0, 0, 0, s21_NORMAL_VALUE);
    s21_decimal ten = s21_init_decimal(10, 0, 0, 0, s21_NORMAL_VALUE);
    int scale = s21_get_scale(*number);
    while (!s21_is_equal(s21_int_div_or_mod(*number, ten, 0), zero) && scale > temp_scale) {
        *number = s21_int_div_or_mod(*number, ten, 1);
        scale--;
    }
    if ((unsigned int)scale != s21_get_scale(*number))
        s21_set_scale(number, scale);
}
