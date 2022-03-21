// TESTS FOR s21_pow()
#ifdef TEST_NAME_pow
double valForPow[10] = {0, 1, 2.123, 5.00345, 4.34573945454, 9,
                        11.348957, 10.003, 19, 20};
START_TEST(s21_pow_test_1) {
    for (double exp = 1; exp <= 7; exp += 0.01) {
        long double orig = powl(valForPow[_i], exp);
        long double s21 = s21_pow(valForPow[_i], exp);
        // printf("%lf^%lf | %.8Lf - %.8Lf\n", valForPow[_i], exp, orig, s21);
        ck_assert_ldouble_eq_tol(orig, s21, epsilon);
    }
}
END_TEST

START_TEST(s21_pow_test_2) {
    for (double exp = -7; exp < -1; exp += 0.01) {
        long double orig = powl(valForPow[_i], exp);
        long double s21 = s21_pow(valForPow[_i], exp);
        // printf("%lf^%lf | %.8Lf - %.8Lf\n", valForPow[_i], exp, orig, s21);
        ck_assert_ldouble_eq_tol(orig, s21, epsilon);
    }
}
END_TEST

START_TEST(s21_pow_test_3) {
    double x = -0.0;
    double y = -3;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    // ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_infinite(org);
    ck_assert_ldouble_infinite(s21);
    x = +0.0;
    y = -3;
    s21 = s21_pow(x, y);
    org = pow(x, y);
    ck_assert_ldouble_infinite(org);
    ck_assert_ldouble_infinite(s21);
    x = +0.0;
    y = -2;
    s21 = s21_pow(x, y);
    org = pow(x, y);
    ck_assert_ldouble_infinite(org);
    ck_assert_ldouble_infinite(s21);
}
END_TEST

START_TEST(s21_pow_test_4) {
    double x = -1;
    double y = -INFINITY;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_5) {
    double x = 0.01;
    double y = -INFINITY;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_6) {
    double x = -1;
    double y = 0.0001;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_nan(org);
    ck_assert_ldouble_nan(s21);
}
END_TEST
START_TEST(s21_pow_test_7) {
    double x = 2;
    double y = -INFINITY;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_8) {
    double x = 1;
    double y = NAN;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_9) {
    double x = 0.01;
    double y = INFINITY;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_10) {
    double x = 10;
    double y = INFINITY;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_11) {
    double x = -INFINITY;
    double y = -1;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_eq(org, -0);
}
END_TEST


START_TEST(s21_pow_test_12) {
    double x = -INFINITY;
    double y = -2;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_eq(org, 0);
}
END_TEST

START_TEST(s21_pow_test_13) {
    double x = -INFINITY;
    double y = 2;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_14) {
    double x = -INFINITY;
    double y = 3;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_15) {
    double x = INFINITY;
    double y = -1;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_pow_test_16) {
    double x = INFINITY;
    double y = 1;
    long double s21 = s21_pow(x, y);
    long double org = pow(x, y);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST
#endif  // END TESTS FOR s21_pow
