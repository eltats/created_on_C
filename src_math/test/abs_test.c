// TESTS FOR s21_abs()
#ifdef TEST_NAME_abs
START_TEST(s21_abs_test_1) {
     int x = INT_MIN;
    int x1 = INT_MIN;
    long int test1 = s21_abs(x);
    long int test2 = labs(x1);
#if defined S21_APPLE
    ck_assert_int_eq(test1, test2);
#elif defined S21_MINGW
    ck_assert_int_eq(test1, test2);
#elif defined S21_LINUX
    ck_assert_int_eq(test1, test2);
#endif
}
END_TEST

START_TEST(s21_abs_test_2) {
    int x = -0;
    int x1 = -0;
    long int test1 = s21_abs(x);
    long int test2 = abs(x1);
    ck_assert_int_eq(test1, test2);
    ck_assert_int_eq(test1, 0);
}
END_TEST

START_TEST(s21_abs_test_3) {
    int x = 0;
    int x1 = 0;
    long int test1 = s21_abs(x);
    long int test2 = abs(x1);
    ck_assert_int_eq(test1, test2);
    ck_assert_int_eq(test1, 0);
}
END_TEST

START_TEST(s21_abs_test_4) {
    int x = -32769;
    int x1 = -32769;
    long int test1 = s21_abs(x);
    long int test2 = abs(x1);
    ck_assert_int_eq(test1, test2);
    ck_assert_int_eq(test2, 32769);
}
END_TEST

START_TEST(s21_abs_test_5) {
    int x = -2147483648;
    int x1 = -2147483648;
    long int test1 = s21_abs(x);
    long int test2 = abs(x1);
#if defined S21_APPLE
    // uncomment one line below after check for mac
    ck_assert_int_ne(test1, test2);
    // ck_assert_int_eq(test1, 2147483648);
    // ck_assert_int_eq(test2, -2147483648);
#elif defined S21_MINGW
    ck_assert_int_eq(test1, test2);
    ck_assert_int_eq(test1,  -2147483648);
    ck_assert_int_eq(test2,  -2147483648);
#elif defined S21_LINUX
    ck_assert_int_eq(test1, 2147483648);
    ck_assert_int_eq(test2, -2147483648);
#endif
}
END_TEST

START_TEST(s21_abs_test_6) {
    // for (int x = -32769; x <= 32769; x++) {
    for (int x = -30; x <= 32; x++) {
    long int test1 = s21_abs(x);
    long int test2 = abs(x);
    ck_assert_int_eq(test1, test2);
    }
}
END_TEST
#endif  // END TESTS FOR s21_abs()
