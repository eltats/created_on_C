// >>>>>>>>>>>>>>>>>> TESTS FOR s21_acos() >>>>>>>>>>>>>>>>>>>>>>>
#ifdef TEST_NAME_acos
double valForAcos[2000];
void genValForTestAcos() {
    int step = 0.001;
    int count = 0;
    for (double i = -1; i <= 1; i += step, count++) {
        valForAcos[count] = i;
    }
}

START_TEST(s21_acos_test_1) {
    long double orig = acosl(valForAcos[_i]);
    long double s21 = s21_acos(valForAcos[_i]);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST

START_TEST(s21_acos_test_2) {
    long double orig = acosl(NAN);
    long double s21 = s21_acos(NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_acos_test_3) {
    long double orig = acosl(INFINITY);
    long double s21 = s21_acos(INFINITY);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_acos_test_4) {
    long double orig = acosl(-NAN);
    long double s21 = s21_acos(-NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_acos_test) {
    long double s21 = s21_acos(a[_i]);
    long double org = acosl(a[_i]);
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
#endif  // END TESTS FOR s21_acos()
