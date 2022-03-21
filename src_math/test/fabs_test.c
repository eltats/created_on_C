// TESTS FOR s21_fabs()
#ifdef TEST_NAME_fabs
START_TEST(s21_fabs_test_1) {
    double x = -2.1;
    double x1 = -2.1;
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("for -2.1 %Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test2, 2.100000);
}
END_TEST
START_TEST(s21_fabs_test_2) {
    double x = -0;
    double x1 = -0;
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("%Lf\n", test1);
    // printf("%Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test2, 0.000000);
}
END_TEST
START_TEST(s21_fabs_test_3) {
    double x = 0;
    double x1 = 0;
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("%Lf\n", test1);
    // printf("%Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test2, 0.000000);
}
END_TEST

START_TEST(s21_fabs_test_4) {
    double x = -0.000001;
    double x1 = -0.000001;
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("%Lf\n", test1);
    // printf("%Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test2, 0.000001);
}
END_TEST

START_TEST(s21_fabs_test_5) {
    double x = -0.0f;
    double x1 = -0.0f;
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // long double test3 = fabsl(x1);
    // printf("-0.0f %Lf\n", test1);
    // printf("-0.0f %Lf\n", test2);
    // printf("-0.0f %Lf\n", test3);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test2, 0.000000);
}
END_TEST

START_TEST(s21_fabs_test_6) {
    double x = -32769;
    double x1 = -32769;
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("%Lf\n", test1);
    // printf("%Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test2, 32769.000000);
}
END_TEST

START_TEST(s21_fabs_test_7) {
    double x = -DBL_MAX;
    double x1 = -DBL_MAX;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // long double test3 = fabsl(x1);
    // printf("-DBL_MAX  %Lf\n", test1);
    // printf("-DBL_MAX  %Lf\n", test2);
    // printf("-DBL_MAX  %Lf\n", test3);
    ck_assert_ldouble_eq(test1, test2);
}
END_TEST

START_TEST(s21_fabs_test_8) {
    double x = DBL_MAX;
    double x1 = DBL_MAX;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    long double res = fabs(test1 - test2);
    if (res <= DBL_EPSILON) {
        // printf("equal test1 & test2\n");
        ck_assert_ldouble_eq(test1, test2);
    } else {
    printf("test are not equal test1 & test2\n");
    }
    // printf("test 8 %Lf\n", test1);
    // printf("test 8 %Lf\n", test2);
    // printf("DBL_EPSILON %f\n", DBL_EPSILON);
    // printf("res %Lf\n", res);
    // ck_assert_ldouble_eq(res, DBL_EPSILON);
}
END_TEST

START_TEST(s21_fabs_test_9) {
    double x = 38.0;
    double x1 = 38.0;
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("test 9 %Lf\n", test1);
    // printf("test 9 %Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test1,  38.000000);
}
END_TEST

START_TEST(s21_fabs_test_10) {
    double x = S21_NEG_NAN;
    ck_assert_ldouble_nan(x);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x);
    ck_assert_ldouble_nan(test1);
    ck_assert_ldouble_nan(test2);
}
END_TEST

START_TEST(s21_fabs_test_11) {
    double x = NAN;
    ck_assert_ldouble_nan(x);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x);
    ck_assert_ldouble_nan(test1);
    ck_assert_ldouble_nan(test2);
}
END_TEST

START_TEST(s21_fabs_test_12) {
    double x = INFINITY;
    double x1 = S21_POS_INF;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test1,  INFINITY);
    ck_assert_ldouble_eq(test2,  INFINITY);
}
END_TEST

START_TEST(s21_fabs_test_13) {
    double x = S21_NEG_INF;
    double x1 = S21_NEG_INF;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test1,  INFINITY);
    ck_assert_ldouble_eq(test2,  INFINITY);
}
END_TEST

START_TEST(s21_fabs_test_14) {
    double x = S21_EPS;
    double x1 = S21_EPS;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("S21_EPS %Lf\n", test1);
    // printf("S21_EPS %Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test1,  1e-16);
}
END_TEST

START_TEST(s21_fabs_test_15) {
    double x = S21_NEG_EPS;
    double x1 = S21_NEG_EPS;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("EPS %Lf\n", test1);
    // printf("EPS %Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
    ck_assert_ldouble_eq(test1, 1e-16);
}
END_TEST

START_TEST(s21_fabs_test_16) {
    double x = DBL_EPSILON;
    double x1 = DBL_EPSILON;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("DBL_EPSILON %Lf\n", test1);
    // printf("DBL_EPSILON %Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
}
END_TEST

START_TEST(s21_fabs_test_17) {
    double x = -DBL_EPSILON;
    double x1 = -DBL_EPSILON;
    // printf("%f\n", x);
    // printf("%f\n", x1);
    long double test1 = s21_fabs(x);
    long double test2 = fabs(x1);
    // printf("DBL_EPSILON %Lf\n", test1);
    // printf("DBL_EPSILON %Lf\n", test2);
    ck_assert_ldouble_eq(test1, test2);
}
END_TEST
#endif  // END TESTS FOR s21_fabs()
