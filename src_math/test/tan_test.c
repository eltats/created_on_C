// >>>>>>>>>>>>>>>>>> TESTS FOR s21_tan() >>>>>>>>>>>>>>>>>>>>>>>
#ifdef TEST_NAME_tan
double valForTan[1440];
void genValForTestTan() {
    double a = S21_PI / 180;
    int count = 0;
    for (double i = -4 * S21_PI; i <= 4* S21_PI; i += a, count++) {
    valForTan[count] = i;
    }
}
START_TEST(s21_tan_test_1) {
    long double orig = tanl(valForTan[_i]);
    long double s21 = s21_tan(valForTan[_i]);
    if (_i == 90 || _i == 270 || _i == 450 ||
        _i == 630 || _i == 810 || _i == 990 ||
        _i == 1170 || _i == 1350) {
        ck_assert_ldouble_infinite(s21);
    // } else if (_i == 180 || _i == 360 || _i == 540 ||
    //     _i == 720 || _i == 900 || _i == 1080 || _i == 1260) {
    //     ck_assert_ldouble_eq_tol(orig, s21, 6L);

    } else {
        ck_assert_ldouble_eq_tol(orig, s21, epsilon);
    }
}
END_TEST

START_TEST(s21_tan_test_2) {
    long double orig = tanl(NAN);
    long double s21 = s21_tan(NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_tan_test_3) {
    long double orig = tanl(INFINITY);
    long double s21 = s21_tan(INFINITY);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_tan_test_4) {
    long double orig = tanl(-NAN);
    long double s21 = s21_tan(-NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_tan_test) {
    long double s21 = s21_tan(a[_i]);
    long double org = tanl(a[_i]);

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
#endif  // END TESTS FOR s21_tan()
