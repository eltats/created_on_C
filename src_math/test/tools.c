/**
 * @brief функция проверяет, что оба значения NAN с одинаковыми знаками
 * 
 * @param a 
 * @param b 
 * @return 1 - оба значения NAN с одинаковыми знаками
 *         0 - одно из условий не выполняется
 */
int isEqualsNan(long double a, long double b) {
    return s21_isnan(a) == s21_isnan(b);
}

/**
 * @brief функция проверяет, что оба значения INFINITY с одинаковыми знаками
 * 
 * @param a 
 * @param b 
 * @return 1 - оба значения INFINITY с одинаковыми знаками
 *         0 - одно из условий не выполняется
 */
int isEqualsInf(long double a, long double b) {
    return (s21_isinf(a) == s21_isinf(b) && getSign(a) == getSign(b));
}
