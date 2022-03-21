#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t step = 0;
    int countStr1 = 0;
    int countStr2 = 0;
    while (step != n) {
        countStr1 += *str1;
        countStr2 += *str2;
        step++;
        if (countStr1 != countStr2) {
            step = n;
        }
        str1++;
        str2++;
    }
    return countStr1 - countStr2;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i;
    for (i = 0; i < n && src[i] != '\0'; ++i) {}
    if (i != n) {
        for (s21_size_t j = i; j < s21_strlen(src) + 1; ++j) {
            dest[j] = '\0';
        }
    }
    for (s21_size_t j = 0; j < i; ++j) {
        dest[j] = src[j];
    }
    return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    int index = -1;
    int count = 0;
    for (int i = 0; str1[i] != '\0' && index == -1; ++i) {
        for (int j = 0; str2[j] != '\0' ; ++j) {
            if (str1[i] == str2[j]) {
                index = i;
            }
        }
        count++;
    }
    if (index == -1) {
        index = count;
    }
    return index;
}

char *s21_strrchr(const char *str, int c) {
    char *number = S21_NULL;
    for (s21_size_t i = 0; i < s21_strlen(str); ++i) {
        if (str[i] == c) {
            number = (char*)(str + i);
        }
    }
    return number;
}
