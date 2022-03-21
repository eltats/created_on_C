// >>>>>>>>>>>>>>>>>> TESTS FOR s21_sin() >>>>>>>>>>>>>>>>>>>>>>>
#ifdef TEST_NAME_sin
double valForSin[1440];
void genValForTestSin() {
    double a = S21_PI / 180;
    int count = 0;
    for (double i = -4 * S21_PI; i <= 4* S21_PI; i += a, count++) {
        valForSin[count] = i;
    }
}

START_TEST(s21_sin_test_1) {
    long double orig = sinl(valForSin[_i]);
    long double s21 = s21_sin(valForSin[_i]);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST

START_TEST(s21_sin_test_2) {
    long double orig = sinl(NAN);
    long double s21 = s21_sin(NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_sin_test_3) {
    long double orig = sinl(INFINITY);
    long double s21 = s21_sin(INFINITY);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_sin_test_4) {
    long double orig = sinl(-NAN);
    long double s21 = s21_sin(-NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_sin_test) {
    long double s21 = s21_sin(a[_i]);
    long double org = sinl(a[_i]);

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
START_TEST(s21_sin_test_5) {
    long double orig = sinl(S21_PI_2);
    long double s21 = s21_sin(S21_PI_2);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST
START_TEST(s21_sin_test_6) {
    long double orig = sinl(S21_3PI_2);
    long double s21 = s21_sin(S21_3PI_2);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST
#endif  // END TESTS FOR s21_sin()
