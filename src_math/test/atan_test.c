// >>>>>>>>>>>>>>>>>> TESTS FOR s21_atan() >>>>>>>>>>>>>>>>>>>>>>>
#ifdef TEST_NAME_atan
double valForatan[180];
void genValForTestatan() {
    int step = S21_PI / 180;
    int count = 0;
    for (double i = -S21_PI_2; i <= S21_PI_2; i += step, count++) {
        valForatan[count] = i;
    }
}

START_TEST(s21_atan_test_1) {
    long double orig = atanl(valForatan[_i]);
    long double s21 = s21_atan(valForatan[_i]);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST

START_TEST(s21_atan_test_2) {
    long double orig = atanl(NAN);
    long double s21 = s21_atan(NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_atan_test_3) {
    long double orig = atanl(INFINITY);
    long double s21 = s21_atan(INFINITY);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST

START_TEST(s21_atan_test_4) {
    long double orig = atanl(-NAN);
    long double s21 = s21_atan(-NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_atan_test) {
    long double s21 = s21_atan(a[_i]);
    long double org = atanl(a[_i]);

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
#endif  // END TESTS FOR s21_atan()
