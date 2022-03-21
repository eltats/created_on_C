// >>>>>>>>>>>>>>>>>> TESTS FOR s21_asin() >>>>>>>>>>>>>>>>>>>>>>>
#ifdef TEST_NAME_asin
double valForAsin[2000];
void genValForTestAsin() {
    int step = 0.001;
    int count = 0;
    for (double i = -1; i <= 1; i += step, count++) {
        valForAsin[count] = i;
    }
}

START_TEST(s21_asin_test_1) {
    long double orig = asinl(valForAsin[_i]);
    long double s21 = s21_asin(valForAsin[_i]);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST

START_TEST(s21_asin_test_2) {
    long double orig = asinl(NAN);
    long double s21 = s21_asin(NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_asin_test_3) {
    long double orig = asinl(INFINITY);
    long double s21 = s21_asin(INFINITY);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_asin_test_4) {
    long double orig = asinl(-NAN);
    long double s21 = s21_asin(-NAN);
    ck_assert_ldouble_nan(orig);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_asin_test) {
    long double s21 = s21_asin(a[_i]);
    long double org = asinl(a[_i]);

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
#endif  // END TESTS FOR s21_asin()
