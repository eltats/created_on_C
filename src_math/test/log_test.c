#ifdef TEST_NAME_log
START_TEST(s21_log_test) {
    long double s21 = s21_log(a[_i]);
    long double org = logl(a[_i]);
    if (isnan(org)) {
        ck_assert_ldouble_nan(s21);
        ck_assert_ldouble_nan(org);
        ck_assert(isEqualsNan(s21, org) == 1);
    } else if (isinf(org)) {
        ck_assert_ldouble_infinite(s21);
        ck_assert_ldouble_infinite(org);
        ck_assert(isEqualsInf(s21, org) == 1);
    } else {
        ck_assert_ldouble_eq_tol(s21, org, epsilon);
    }
}
END_TEST

double valForlog[1000];
void genValForTestLog() {
    double a = 0.1;
    double step = 0.1;
    int count = 500;
    for (int i = 0; i < count; i++, a += step) {
        valForlog[i] = a;
    }
}
START_TEST(s21_log_test_1) {
    long double orig = logl(valForlog[_i]);
    long double s21 = s21_log(valForlog[_i]);
    // printf("%Lf | %Lf\n", orig, s21);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST
#endif  // END TESTS FOR s21_sqrt
