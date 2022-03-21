// Copyright 2021 - The All Stars Team
#include <stdlib.h>
#include <limits.h>
#include <check.h>
#include <stdio.h>
#include <float.h>
#include "s21_math.h"


#ifdef TEST_NAME_all
#define TEST_NAME_abs
#define TEST_NAME_acos
#define TEST_NAME_asin
#define TEST_NAME_atan
#define TEST_NAME_ceil
#define TEST_NAME_cos
#define TEST_NAME_exp
#define TEST_NAME_fabs
#define TEST_NAME_floor
#define TEST_NAME_fmod
#define TEST_NAME_log
#define TEST_NAME_pow
#define TEST_NAME_sin
#define TEST_NAME_sqrt
#define TEST_NAME_tan
#endif

extern double a[];
double a[] = {NAN, -NAN, -INFINITY, INFINITY-INFINITY, -INFINITY - INFINITY, INFINITY,
                    -0.00, 0.00, -0, 0, -0.000000, 0.000000, -2,
                    1, 1e-4, 2, 2.1234, 2.000001, 1235, 5e+5,
                    -DBL_EPSILON, DBL_EPSILON};


// Подключение тест-кейсов
#include "./test/tools.c"
#include "./test/abs_test.c"
#include "./test/exp_test.c"
#include "./test/sin_test.c"
#include "./test/cos_test.c"
#include "./test/tan_test.c"
#include "./test/asin_test.c"
#include "./test/acos_test.c"
#include "./test/atan_test.c"
#include "./test/sqrt_test.c"
#include "./test/fabs_test.c"
#include "./test/fmod_test.c"
#include "./test/floor_test.c"
#include "./test/ceil_test.c"
#include "./test/pow_test.c"
#include "./test/log_test.c"


// test suite, test cases
Suite * s21_math_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("s21_math");
    // Core test case
    tc_core = tcase_create("Core");

#ifdef TEST_NAME_abs
    tcase_add_test(tc_core, s21_abs_test_1);
    tcase_add_test(tc_core, s21_abs_test_2);
    tcase_add_test(tc_core, s21_abs_test_3);
    tcase_add_test(tc_core, s21_abs_test_4);
    tcase_add_test(tc_core, s21_abs_test_5);
    tcase_add_test(tc_core, s21_abs_test_6);
#endif
#ifdef TEST_NAME_fabs
    tcase_add_test(tc_core, s21_fabs_test_1);
    tcase_add_test(tc_core, s21_fabs_test_2);
    tcase_add_test(tc_core, s21_fabs_test_3);
    tcase_add_test(tc_core, s21_fabs_test_4);
    tcase_add_test(tc_core, s21_fabs_test_5);
    tcase_add_test(tc_core, s21_fabs_test_6);
    tcase_add_test(tc_core, s21_fabs_test_7);
    tcase_add_test(tc_core, s21_fabs_test_8);
    tcase_add_test(tc_core, s21_fabs_test_9);
    tcase_add_test(tc_core, s21_fabs_test_10);
    tcase_add_test(tc_core, s21_fabs_test_11);
    tcase_add_test(tc_core, s21_fabs_test_12);
    tcase_add_test(tc_core, s21_fabs_test_13);
    tcase_add_test(tc_core, s21_fabs_test_14);
    tcase_add_test(tc_core, s21_fabs_test_15);
    tcase_add_test(tc_core, s21_fabs_test_16);
    tcase_add_test(tc_core, s21_fabs_test_17);
#endif
#ifdef TEST_NAME_sqrt
    tcase_add_loop_test(tc_core, s21_sqrt_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif  // TEST_NAME_sqrt
#ifdef TEST_NAME_fmod
    tcase_add_loop_test(tc_core, s21_fmod_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif  // TEST_NAME_fmod
#ifdef TEST_NAME_log
    tcase_add_loop_test(tc_core, s21_log_test, 0, (int)(sizeof(a)/sizeof(a[0])));
    genValForTestLog();
    tcase_add_loop_test(tc_core, s21_log_test_1, 0, 500);
#endif  // TEST_NAME_log
#ifdef TEST_NAME_exp
    genValForTestExp();
    tcase_add_loop_test(tc_core, s21_exp_test_1, 0, 600);
    tcase_add_test(tc_core, s21_exp_test_2);
    tcase_add_test(tc_core, s21_exp_test_3);
    tcase_add_test(tc_core, s21_exp_test_4);
    tcase_add_test(tc_core, s21_exp_test_5);
    tcase_add_test(tc_core, s21_exp_test_6);
    tcase_add_test(tc_core, s21_exp_test_7);
    tcase_add_test(tc_core, s21_exp_test_8);
    tcase_add_test(tc_core, s21_exp_test_9);
#endif
#ifdef TEST_NAME_sin
    genValForTestSin();
    tcase_add_loop_test(tc_core, s21_sin_test_1, 0, 1440);
    tcase_add_test(tc_core, s21_sin_test_2);
    tcase_add_test(tc_core, s21_sin_test_3);
    tcase_add_test(tc_core, s21_sin_test_4);
    tcase_add_test(tc_core, s21_sin_test_5);
    tcase_add_test(tc_core, s21_sin_test_6);
    tcase_add_loop_test(tc_core, s21_sin_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_cos
    genValForTestCos();
    tcase_add_loop_test(tc_core, s21_cos_test_1, 0, 1440);
    tcase_add_test(tc_core, s21_cos_test_2);
    tcase_add_test(tc_core, s21_cos_test_3);
    tcase_add_test(tc_core, s21_cos_test_4);
    tcase_add_test(tc_core, s21_cos_test_5);
    tcase_add_test(tc_core, s21_cos_test_6);
    tcase_add_test(tc_core, s21_cos_test_7);
    tcase_add_loop_test(tc_core, s21_cos_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_tan
    genValForTestTan();
    tcase_add_loop_test(tc_core, s21_tan_test_1, 0, 1440);
    tcase_add_test(tc_core, s21_tan_test_2);
    tcase_add_test(tc_core, s21_tan_test_3);
    tcase_add_test(tc_core, s21_tan_test_4);
    tcase_add_loop_test(tc_core, s21_tan_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_asin
    tcase_add_loop_test(tc_core, s21_asin_test_1, 0, 2000);
    tcase_add_test(tc_core, s21_asin_test_2);
    tcase_add_test(tc_core, s21_asin_test_3);
    tcase_add_test(tc_core, s21_asin_test_4);
    tcase_add_loop_test(tc_core, s21_asin_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_acos
    tcase_add_loop_test(tc_core, s21_acos_test_1, 0, 2000);
    tcase_add_test(tc_core, s21_acos_test_2);
    tcase_add_test(tc_core, s21_acos_test_3);
    tcase_add_test(tc_core, s21_acos_test_4);
    tcase_add_loop_test(tc_core, s21_acos_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_atan
    tcase_add_loop_test(tc_core, s21_atan_test_1, 0, 180);
    tcase_add_test(tc_core, s21_atan_test_2);
    tcase_add_test(tc_core, s21_atan_test_3);
    tcase_add_test(tc_core, s21_atan_test_4);
    tcase_add_loop_test(tc_core, s21_atan_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_pow
    tcase_add_loop_test(tc_core, s21_pow_test_1, 0, 10);
    tcase_add_test(tc_core, s21_pow_test_4);
    tcase_add_test(tc_core, s21_pow_test_5);
    tcase_add_test(tc_core, s21_pow_test_6);
    tcase_add_test(tc_core, s21_pow_test_7);
    tcase_add_test(tc_core, s21_pow_test_8);
    tcase_add_test(tc_core, s21_pow_test_9);
    tcase_add_test(tc_core, s21_pow_test_10);
    tcase_add_test(tc_core, s21_pow_test_11);
    tcase_add_test(tc_core, s21_pow_test_12);
    tcase_add_test(tc_core, s21_pow_test_13);
    tcase_add_test(tc_core, s21_pow_test_14);
    tcase_add_test(tc_core, s21_pow_test_15);
    tcase_add_test(tc_core, s21_pow_test_16);
#endif
#ifdef TEST_NAME_floor
    genValForTestFloor();
    tcase_add_loop_test(tc_core, s21_floor_test_1, 0, 2000);
    tcase_add_test(tc_core, s21_floor_test_0);
    tcase_add_test(tc_core, s21_floor_test_3);
    tcase_add_test(tc_core, s21_floor_test_4);
    tcase_add_test(tc_core, s21_floor_test_5);
    tcase_add_test(tc_core, s21_floor_test_6);
    tcase_add_test(tc_core, s21_floor_test_7);
    tcase_add_test(tc_core, s21_floor_test_8);
    tcase_add_test(tc_core, s21_floor_test_11);
    tcase_add_test(tc_core, s21_floor_test_12);
    tcase_add_test(tc_core, s21_floor_test_13);
    tcase_add_test(tc_core, s21_floor_test_14);
    tcase_add_test(tc_core, s21_floor_test_15);
    tcase_add_test(tc_core, s21_floor_test_16);
    tcase_add_loop_test(tc_core, s21_floor_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_ceil
    genValForTestceil();
    tcase_add_loop_test(tc_core, s21_ceil_test_1, 0, 2000);
    tcase_add_test(tc_core, s21_ceil_test_01);
    tcase_add_test(tc_core, s21_ceil_test_3);
    tcase_add_test(tc_core, s21_ceil_test_4);
    tcase_add_test(tc_core, s21_ceil_test_5);
    tcase_add_test(tc_core, s21_ceil_test_6);
    tcase_add_test(tc_core, s21_ceil_test_7);
    tcase_add_test(tc_core, s21_ceil_test_8);
    tcase_add_test(tc_core, s21_ceil_test_11);
    tcase_add_test(tc_core, s21_ceil_test_12);
    tcase_add_test(tc_core, s21_ceil_test_13);
    tcase_add_test(tc_core, s21_ceil_test_14);
    tcase_add_test(tc_core, s21_ceil_test_15);
    tcase_add_test(tc_core, s21_ceil_test_16);
    tcase_add_loop_test(tc_core, s21_ceil_test, 0, (int)(sizeof(a)/sizeof(a[0])));
#endif
#ifdef TEST_NAME_pow
    tcase_add_loop_test(tc_core, s21_pow_test_1, 0, 10);
    tcase_add_loop_test(tc_core, s21_pow_test_2, 1, 10);
    // tcase_add_test(tc_core, s21_pow_test_2);
    tcase_add_test(tc_core, s21_pow_test_3);
    tcase_add_test(tc_core, s21_pow_test_4);
    tcase_add_test(tc_core, s21_pow_test_5);
    tcase_add_test(tc_core, s21_pow_test_6);
    tcase_add_test(tc_core, s21_pow_test_7);
    tcase_add_test(tc_core, s21_pow_test_8);
    tcase_add_test(tc_core, s21_pow_test_9);
    tcase_add_test(tc_core, s21_pow_test_10);
    tcase_add_test(tc_core, s21_pow_test_11);
    tcase_add_test(tc_core, s21_pow_test_12);
    tcase_add_test(tc_core, s21_pow_test_13);
    tcase_add_test(tc_core, s21_pow_test_14);
    tcase_add_test(tc_core, s21_pow_test_15);
    tcase_add_test(tc_core, s21_pow_test_16);
#endif
    suite_add_tcase(s, tc_core);
    return s;
}

int main() {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = s21_math_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
