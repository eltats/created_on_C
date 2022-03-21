// Copyright 2021 - The All Stars Team
#include "s21_math.h"

/**
 * @brief
 *
 * @param x
 * @return long int
 */
long int s21_abs(int x) {
    /* if (x < 0) {
      x = -1 * x;
    }
    return x; 
    long int res = x;
      if (res < 0) {
      res = -1 * res;
    }
    return res;
    */
    long int res = x;
    int y = getSign(res);
    if (y == 1) {
    res = -1 * res;
    }
    return res;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 */
long double s21_fabs(double x) {
    /*
    if (x < 0) {
      x = -1 * x;
    }
      if (x == -0.000000) {
    x = 0.000000;
    }
    return x;
    */
    long double res = x;
    int y = getSign(res);
    if (y == 1) {
    res = -1 * res;
    }
    return res;
}

long double s21_pow(double base, double exp) {
    int rate = 6;
    long double res = 0.0;
    if (base == 0) {
        if (isWholeInteger(exp, rate) && exp < 0 && ((long int)exp % 2 != 0)) {
            // odd
            if (getSign(base)) {
                // -
                res = S21_NEG_INF;
            } else {
                // +
                res = S21_POS_INF;
            }
        } else if (isWholeInteger(exp, rate) && exp < 0 && ((long int)exp % 2 == 0)) {
            // not odd
            res = S21_POS_INF;
        } else if (isWholeInteger(exp, rate) && exp > 0 && ((long int)exp % 2 != 0)) {
            if (getSign(base)) {
                // -
                res = -0.0;
            } else {
                // +
                res = +0.0;
            }
        } else if (isWholeInteger(exp, rate) && exp > 0 && ((long int)exp % 2 == 0)) {
            res = +0.0;
        }

    } else if (base == 1) {
        res = 1.0;

    } else if (base == -1 && (exp == S21_POS_INF || exp == S21_NEG_INF)) {
        res = 1.0;

    } else if (s21_isinf(base)) {
        if (getSign(base)) {
            // -INF
            if (exp < 0 && isWholeInteger(exp, rate) && ((long int)exp % 2 != 0))
                res = -0.0;
            else if (exp < 0 && isWholeInteger(exp, rate) && ((long int)exp % 2 != 0))
                res = +0.0;
            else if (exp > 0 && isWholeInteger(exp, rate) && ((long int)exp % 2 != 0))
                res = S21_NEG_INF;
            else if (exp > 0 && isWholeInteger(exp, rate) && ((long int)exp % 2 == 0))
                res = S21_POS_INF;
        } else {
            // +INF
            if (exp > 0)
                res = S21_POS_INF;
            else if (exp < 0)
                res = +0.0;
        }

    } else if (base < 0 && !s21_isinf(base) && !s21_isinf(exp) && !isWholeInteger(exp, rate)) {
        res = -S21_NAN;

    } else if (base != 0 && s21_isinf(exp)) {
        if (getSign(exp)) {
            if (s21_fabs(base) < 1)
                res = S21_POS_INF;
            else
                res = +0.0;
        } else {
            if (s21_fabs(base) < 1)
                res = +0.0;
            else
                res = S21_POS_INF;
        }

    } else if (!isWholeInteger(exp, rate)) {
        // возведение в дробную степень
        long int whole_exp = (long int) exp;
        double fraction_exp = exp - whole_exp;
        res = s21_powInteger(base, whole_exp) * s21_exp(fraction_exp * s21_log(base));
        res -= 0.0000005;
    } else {
        // возведение в целую степень
        res = s21_powInteger(base, (int) exp);
    }

    // res = expl(exp * logl(base));
    return res;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 * If x is a NaN, a NaN is returned.
 * If x is +0 (-0), +0 (-0) is returned.
 * If x is positive infinity, positive infinity is returned.
 * If x is less than -0, a domain error occurs, and a NaN is returned.
 */
long double s21_sqrt(double x) {
    long double x1 = 1;
    if (x > 0.0 && x < S21_POS_INF) {
        long double x0;
        do {
            x0 = x1;
            x1 = 0.5 * (x0 + x / x0);
        } while (s21_fabs(x1 - x0) >= S21_EPS);
    } else if (x < -0.0) {
        x1 = -S21_NAN;
    } else {
        x1 = x;
    }
    return x1;
}

/**
 * @brief These  functions  compute  the  floating-point remainder of dividing x
 * by y.  The return value is x - n * y, where n is the quotient of x / y,
 * rounded toward zero to an integer.
 * @param x
 * @param y
 * @return long double
 *         On success, these functions return the value x - n*y, for some integer n, 
 *         such that the returned value has the same sign as
 *         x and a magnitude less than the magnitude of y.
 *      If x or y is a NaN, a NaN is returned.
 *      If x is an infinity, a domain error occurs, and a NaN is returned.
 *      If y is zero, a domain error occurs, and a NaN is returned.
 *      If x is +0 (-0), and y is not zero, +0 (-0) is returned.
 */
long double s21_fmod(double x, double y) {
    long double res;
    int sign_x = getSign(x), sign_y = getSign(y);

    if (s21_isnan(x)) {
        if (sign_x && (!s21_isnan(y) || sign_y)) {
            res = -S21_NAN;
        } else {
            res = S21_NAN;
        }
    } else if (s21_isnan(y)) {
        if (sign_y) {
            res = -S21_NAN;
        } else {
            res = S21_NAN;
        }
    } else if (s21_isinf(x) || y == 0.0) {
        res = -S21_NAN;
    } else if (s21_fabs(y) < epsilon) {
        res = getSign(x) ? -0.0f : 0.0f;
    } else if ((x == 0.0 && y != 0.0) || s21_isinf(y)) {
        res = x;
    } else {
        if (s21_fabs(x) >= s21_fabs(y)) {
            long double fx = getSign(x) ? -x : x;
            long double fy = getSign(y) ? -y : y;
            long double res1 = s21_floor(fx / fy) * fy;
            if (res1 > fx) {
                res1 -= fy;
            }
            res = fx - res1;
        } else {
            res = x;
        }
        if (sign_x != getSign(res))
            res *= -1;
    }
    return res;
}

/**
 * @brief Арксинус угла 
 *The asin() functions returns the value in range of [-π/2, +π/2] in radians. 
 If the parameter passed to the asin() function is less than -1 or greater than 1, the function returns NaN (not a number).
 * @param x
 * @return long double
 */
long double s21_asin(double x) {
    long double asin = 0;
    int sign = 1;
    if (getSign(x)) sign = -1;
    x = s21_fabs(x);
    if (s21_isnan(x) || x > 1) {
            asin = S21_NAN;
    } else if (x > 1/s21_sqrt(2)) {
        asin = S21_PI_2 - s21_asin(s21_sqrt(1-x*x));
    } else {
        long double dif = 1;
        long double result = x;
        int k = 0;
        while (dif > 0.000000) {
            long double buf = 1;
            for (int i = 1; i <= 2 * k + 1; ++i) {
                buf *= x;
                if (i % 2 == 0 || i == 2 * k + 1) {
                    buf /= i;
                } else {
                    buf *= i;
                }
            }
            asin += buf;
            if (k > 0) {
                dif = s21_fabs(asin - result);
            }
            result = asin;
            k++;
        }
    }
    return sign*asin;
}

/**
 * @brief Арккосинус угла
 * TThe acos() functions returns the value in range of [0.0, π] in radians. 
 * If the parameter passed to the acos() function is less than -1 or greater than 1, the function returns NaN (not a number).
 * @param x
 * @return long double
 */
long double s21_acos(double x) {
    return (S21_PI_2 - s21_asin(x));
}

/**
 * @brief Арктангенс угла
 *
 * @param x
 * @return long double
 */
long double s21_atan(double x) {
    long double res;
    if (s21_isnan(x)) {
        res = x;  // S21_NAN;
    } else if (s21_isinf(x)) {
        if (getSign(x))
            res = -S21_PI_2;
        else
            res = S21_PI_2;
    } else {
        res = s21_asin(x/s21_sqrt(1+x*x));
    }
    return res;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 */
long double s21_ceil(double x) {
  if (x == S21_NAN) {
    x = S21_NAN;
  } else if (x == S21_POS_INF) {
    x = S21_POS_INF;
  } else if (x == S21_NEG_INF) {
    x = S21_NEG_INF;
  } else if (x > 0 && x != (long long int)x) {
    x = (long long int)x + 1;
  } else if (x < 0) {
    x = (long long int)x;
  } else {
    x = x;
  }
  return x;
}

/**
 * @brief Косинус угла
 *
 * @param x
 * @return long double
 */
long double s21_cos(double x) {
    long double cos = 0;
    if (x < -2 * S21_PI || x > 2 * S21_PI) x = normalizeToRadian(x);
    x = s21_fabs(x);
    if (s21_isinf(x)) {
        cos = -S21_NAN;
    } else if (s21_isnan(x)) {
        if (getSign(x))
            cos = -S21_NAN;
        else
            cos = S21_NAN;
    } else if (x == S21_PI_2) {
        cos = 0;
    } else if (x == S21_PI) {
        cos = -1.0;
    } else if (x == 0 || x == 2 * S21_PI) {
        cos = 1.0;
    } else if (x == S21_3PI_2) {
        cos = 0.0;
    } else if (x > 0 && x < S21_PI / 2) {  // 1-89
        cos = getCos(x);
    } else if (x > S21_PI_2 && x < S21_PI) {  // 91-179
        cos = -getCos(S21_PI_2 - (x - S21_PI_2));
    } else if (x > S21_PI && x < S21_3PI_2) {  // 181-269
        cos = -1.0 * (getCos(x - S21_PI));
    } else if (x > S21_3PI_2 / 2 && x < 2 * S21_PI) {
        cos = getCos((S21_PI_2) - (x - (S21_3PI_2)));
    }
    return cos;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 */
long double s21_exp(double x) {
  long double temp = 0, sum = 0, expi = 0;
  if (x == S21_POS_INF) {
    expi = S21_POS_INF;
  } else if (x == S21_NEG_INF) {
    expi = expi;
  } else {
    __int128_t whole = (__int128_t)x;
    long double part = x - whole;
    __int128_t facT = 1;
    for (int i = 2; i <= 21; ++i) {
        facT *= i;
      temp = s21_powInteger(part, i) / facT;
      // temp = s21_powInteger(part, i) / s21_fact(i);
      sum += temp;
    }
    expi = 1 + part + sum;
    expi *= s21_powInteger(S21_E, whole);
  }
  return expi;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 */
long double s21_floor(double x) {
  if (x == S21_NAN) {
    x = S21_NAN;
  } else if (x == S21_POS_INF) {
    x = S21_POS_INF;
  } else if (x == S21_NEG_INF) {
    x = S21_NEG_INF;
  } else if (x > 0 && x != (long long int)x) {
    x = (long long int)x;
  } else if (x < 0 && x != (long long int)x) {
    x = (long long int)x - 1;
  } else {
    x = x;
  }
  return x;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 */
long double s21_log(double x) {
    int count_10 = 0, count_2 = 0;
    long double slack = 0.0, tay = 0.0;
    if (x != x) {
        tay = x;  // S21_NAN;
    } else if (x == 0.0) {
        tay = S21_NEG_INF;
    } else if (x < 0.0) {
        tay = S21_NAN;
    } else if (x == S21_POS_INF) {
        tay = S21_POS_INF;
    } else if (x == S21_NEG_INF) {
        tay = S21_NAN;
    } else {
        if (x < 1) {
            while (x < 1) {
                x *= 10;
            count_10++;
        }
        slack = count_10 * S21_LOG10;
        tay = s21_taylor(x) - slack;
    } else {
        while (x > 10) {
            x /= 10;
            count_10++;
        }
        while (x >= 2) {
            x /= 2;
            count_2++;
        }
        slack = count_10 * S21_LOG10 + count_2 * S21_LOG2;
        tay = s21_taylor(x) + slack;
    }
  }
  return tay;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 */
long double s21_sin(double x) {
    int sign = 1;
    long double sin = 0;
    if (getSign(x)) sign = -1;
    if (x < -2 * S21_PI || x > 2 * S21_PI) x = normalizeToRadian(x);
    x = s21_fabs(x);
    if (s21_isinf(x)) {
        sin = -S21_NAN;
    } else if (s21_isnan(x)) {
        if (getSign(x))
            sin = -S21_NAN;
        else
            sin = S21_NAN;
    } else if (x == S21_PI_2) {
        sin = 1;
    } else if (x == 0 || x == S21_PI || x == 2 * S21_PI) {
        sin = 0.0;
    } else if (x == S21_3PI_2) {
        sin = -1;
    } else if (x > 0 && x < S21_PI / 2) {
        sin = getSin(x);
    } else if (x > S21_PI_2 && x < S21_PI) {
        sin = getSin(S21_PI_2 - (x - S21_PI_2));
    } else if (x > S21_PI && x < (3 * S21_PI / 2)) {
        sin = -1.0 * (getSin(x - S21_PI));
    } else if (x > 3 * S21_PI / 2 && x < 2 * S21_PI) {
        sin = -1.0 * (getSin((S21_PI_2) - (x - (S21_3PI_2))));
    }
    return sin * sign;
}

/**
 * @brief
 *
 * @param x
 * @return long double
 */
long double s21_tan(double x) {
    long double tan = 0.0;
    long double sin = s21_sin(x);
    long double cos = s21_cos(x);
    double x1 = (x < -2 * S21_PI || x > 2 * S21_PI) ? normalizeToRadian(x) : x;
    if (s21_isinf(x)) {
        tan = -S21_NAN;
    } else if (s21_isnan(x)) {
        tan = x;  // -S21_NAN;
    } else if (x1 == 0) {
        tan = (x > 0) ? -0.0 : 0.0;
    } else if (s21_fabs(x1) == S21_PI || s21_fabs(x1) == 2 * S21_PI) {
        tan = (getSign(x)) ? 0.0 : -0.0;
    } else if (cos == 0 || dEquals(cos, 0.0, 6) == 0) {
        tan = S21_POS_INF;
    } else {
        tan = sin / cos;
    }
    return tan;
}

/**
 * @brief
 *
 * @param x
 * @return int
 */
int s21_isnan(double x) {
    return x != x;
}

/**
 * @brief
 *
 * @param x
 * @return int
 */
int s21_isinf(double x) {
    return !s21_isnan(x) && s21_isnan(x - x);
}

/** @brief Определяет является ли число целым
 *  @param ld_num число
 *  @param rate количество значащих разрядов в числе
 *  @return 0 - число дробное, 1 - число целое
 */
int isWholeInteger(long double ld_num, int rate) {
    int res = 0;
    if (ld_num == 0) {
        res = 1;
    } else {
        res = ((long long)((ld_num - (long long) ld_num) * s21_powInteger(10, rate)) != 0) ? 0 : 1;
    }
    return res;
}

/**
 * @brief Сравнивает два дробных числа, до указанной разрядности
 *        с учетом правил округления (1.4 == 1.0, 1.5 == 2.0)
 * 
 * @param a число 1
 * @param b число 2
 * @param rate разрядность до которой проводить сравнение
 * @return int 0 - числа равны, Отрицательное a<b, Положительное a>b
 */
int dEquals(long double a, long double b, int rate) {
    int res = 0;
    long long mult = s21_powInteger(10, rate + 1);
    long long exp_a = (long long) a;
    long long exp_b = (long long) b;
    if (exp_a == exp_b) {
        long long fraction_a = mult * (a - exp_a);
        long int a1 = fraction_a / 10;
        if (a1 && (fraction_a % a1) > 4) a1++;
        long long fraction_b = mult * (b - exp_b);
        long int b1 = fraction_b / 10;
        if (b1 && (fraction_b % b1 > 4)) b1++;
        if (a1 == b1) {
            res = 0;
        } else {
            res = (a1 < b1) ? -1 : 1;
        }
    } else {
        res = (exp_a < exp_b) ? -1 : 1;
    }
    return res;
}

/**
 * @brief Возводит число в челую степень число
 * 
 * @param base положительное или отрицательное число
 * @param exp степень (целое число)
 * @return long double base в степени exp
 */
long double s21_powInteger(long double base, int exp) {
    long double res;
    if (exp < 0) {
        res = 1 / (base * s21_powInteger(base, (-exp) - 1));
    } else if (exp == 0) {
        res = 1;
    } else if (exp == 1) {
        res = base;
    } else {
        res = base * s21_powInteger(base, exp - 1);
    }
    return res;
}

/**
 * @brief Get the Sign double
 * 
 * @param x number
 * @return int sign is 1 negative  0 positive
 */
int getSign(double x) {
    union {
    double value;
    unsigned char   array[sizeof(double)];
    } id;
    id.value = x;
    unsigned a = id.array[sizeof(double) - 1];
    a = a >> 7;
    return a;
}

/**
 * @brief factorial
 * 
 * @param n 
 * @return long int 
 */
long int s21_fact(int n) {
    return n <= 0 ? 1 : n * s21_fact(n-1);
}

/**
 * @brief Нормализует число приводя его к диапазону -2PI +2PI
 * 
 * @param x Нормализуемое число
 * @return double число в диапазоне -2PI +2PI
 */
double normalizeToRadian(double x) {
    double a = x / (2 * S21_PI);
    long int b = (long int) a + ((x > 0) ? 0.5 : -0.5);
    double res;
    if (b == 0)
        res = (x < 0) ? -0.0 : 0.0;
    else
        res =  2 * S21_PI * (a - (double) b);
    return res;
}

// возвращает sin числа от 0 ..PI/2
long double getSin(double x) {
    int dip = 7;
    long double sin = 0;
    for (int i = 0; i < dip; i++) {
        sin += s21_powInteger(-1, i) * s21_powInteger(x, 2 * i + 1) / s21_fact(2 * i + 1);
    }
    return sin;
}

// возвращает cos числа от 0 ..PI/2
long double getCos(double x) {
    int dip = 9;
    long double cos = 0;
    for (int i = 0; i < dip; i++) {
        cos += s21_powInteger(-1, i) * s21_powInteger(x, 2 * i) / s21_fact(2 * i);
    }
    return cos;
}

long double s21_taylor(double x) {
    double sum = 0.0;
    x = (x - 1) / (x + 1);
    for (int i = 3; i <= 150; i += 2) {
        sum += s21_powInteger(x, i) / i;
    }
    return (sum + x) * 2;
}
