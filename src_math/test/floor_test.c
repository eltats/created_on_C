// TESTS FOR s21_floor()
#ifdef TEST_NAME_floor
double valForFloor[1000];
void genValForTestFloor() {
    double step = 0.1;
    int count = 0;
    for (int i = -10.99; i < 10.99; i++, i += step, count++) {
        // printf("%.6lf\n", a);
        valForFloor[count] = i;
    }
}

START_TEST(s21_floor_test_0) {
    long double orig = floorl(valForFloor[_i]);
    long double s21 = s21_floor(valForFloor[_i]);
    ck_assert_ldouble_eq_tol(orig, s21, epsilon);
}
END_TEST

START_TEST(s21_floor_test_1) {
    double x = -0.0f;
    double x1 = -0.0f;
    long double s21 = s21_floor(x);
    long double org = floor(x1);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_floor_test_3) {
    double x = 0;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_eq(s21, 0.000000);
}
END_TEST

START_TEST(s21_floor_test_4) {
    double x = -0;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_eq(s21, -0.000000);
}
END_TEST

START_TEST(s21_floor_test_5) {
    double x = -0.000001;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_eq(s21, -1.000000);
}
END_TEST

START_TEST(s21_floor_test_6) {
    double x = S21_EPS;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(s21, 0.000000);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST
START_TEST(s21_floor_test_7) {
    double x = S21_NEG_EPS;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(s21, -1);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_floor_test_8) {
    double x = -1000000.000099;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_floor_test_11) {
    double x = S21_NEG_NAN;
    long double s21 = s21_floor(x);
    long double org = floorl(x);
    ck_assert_ldouble_nan(org);
    ck_assert_ldouble_nan(s21);
}
END_TEST


START_TEST(s21_floor_test_12) {
    double x = S21_NAN;
    ck_assert_ldouble_nan(x);
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_nan(org);
    ck_assert_ldouble_nan(s21);
}
END_TEST

START_TEST(s21_floor_test_13) {
    double x = INFINITY;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_eq(s21,  INFINITY);
    ck_assert_ldouble_eq(org,  INFINITY);
}
END_TEST

START_TEST(s21_floor_test_14) {
    double x = S21_NEG_INF;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
    ck_assert_ldouble_eq(s21,  -INFINITY);
    ck_assert_ldouble_eq(org,  -INFINITY);
}
END_TEST

START_TEST(s21_floor_test_15) {
    double x = DBL_EPSILON;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_floor_test_16) {
    double x = -DBL_EPSILON;
    long double s21 = s21_floor(x);
    long double org = floor(x);
    ck_assert_ldouble_eq(org, s21);
}
END_TEST

START_TEST(s21_floor_test) {
    long double s21 = s21_floor(a[_i]);
    long double org = floor(a[_i]);

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
#endif  // END TESTS FOR s21_floor()
