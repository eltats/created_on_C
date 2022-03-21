// TESTS FOR s21_exp()
#ifdef TEST_NAME_exp
double valForExp[1000];
void genValForTestExp() {
    double a = -30.0;
    double step = 0.1;
    int count = 580;
    for (int i = 0; i < count; i++, a += step) {
        valForExp[i] = a;
    }
}

START_TEST(s21_exp_test_1) {
    long double orig = expl(valForExp[_i]);
    long double s21 = s21_exp(valForExp[_i]);
    // printf("%Lf | %Lf\n", orig, s21);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST
#endif  // END TESTS FOR s21_exp()

// TESTS FOR s21_exp()
#ifdef TEST_NAME_exp

START_TEST(s21_exp_test_2) {
    double x = -0.0f;
    ck_assert_ldouble_eq(s21_exp(x), 1);
    ck_assert_ldouble_eq(s21_exp(x), exp(x));
}
END_TEST
START_TEST(s21_exp_test_3) {
    double x = -0.000001;
    ck_assert_ldouble_eq_tol(s21_exp(x), exp(x), epsilon);
}
END_TEST
START_TEST(s21_exp_test_4) {
    double x = DBL_EPSILON;
    ck_assert_ldouble_eq(s21_exp(x), 1.0000000000000002);
    ck_assert_ldouble_eq(s21_exp(x), exp(x));
}
END_TEST
START_TEST(s21_exp_test_5) {
    double x = -DBL_EPSILON;
    ck_assert_ldouble_eq(s21_exp(x), 0.9999999999999998);
    ck_assert_ldouble_eq(s21_exp(x), exp(x));
}
END_TEST
START_TEST(s21_exp_test_6) {
    double x = NAN;
    long double test1 = s21_exp(x);
    long double test2 = exp(x);
    ck_assert_ldouble_nan(test1);
    ck_assert_ldouble_nan(test2);
}
END_TEST
START_TEST(s21_exp_test_7) {
    double x = -NAN;
    long double test1 = s21_exp(x);
    long double test2 = exp(x);
    ck_assert_ldouble_nan(test1);
    ck_assert_ldouble_nan(test2);
}
END_TEST
START_TEST(s21_exp_test_8) {
    double x = -INFINITY;
    ck_assert_ldouble_eq(s21_exp(x), exp(x));
}
END_TEST
START_TEST(s21_exp_test_9) {
    double x = INFINITY;
    ck_assert_ldouble_eq(s21_exp(x), exp(x));
}
END_TEST

#endif  // END TESTS FOR s21_exp()
