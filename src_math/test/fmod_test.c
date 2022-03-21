#ifdef TEST_NAME_fmod
START_TEST(s21_fmod_test) {
    long double s21;
    long double org;

        for (int j = 0; j < (int)(sizeof(a) / sizeof(a[0])); j++) {
            if (j != _i) {
                org = fmodl(a[_i], a[j]);
                s21 = s21_fmod(a[_i], a[j]);
                if (isnan(org)) {
                    ck_assert(isEqualsNan(s21, org) == 1);
                } else if (isinf(org)) {
                    ck_assert(isEqualsInf(s21, org) == 1);
                } else {
                    ck_assert_ldouble_eq_tol(s21, org, epsilon);
                }
            }
        }
}
END_TEST
#endif  // END TESTS FOR s21_fmod
