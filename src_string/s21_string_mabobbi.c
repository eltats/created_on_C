#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    char *tsed = dest;
    const char *crs = src;
    while (n--)
      *tsed++ = *crs++;
    return dest;
}

s21_size_t s21_strlen(const char *str) {
    unsigned long len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    int count = 0;
    char *result = S21_NULL;
    while (count == 0) {
        int j = 0, i = 0, index = 0;
        for (i = 0; str1[i] != '\0' && count == 0; ++i) {
            for (j = 0; str2[j] != '\0'; ++j) {
                if (str1[i] == str2[j]) {
                    count = 1;
                    index = i;
                    result = (char*)(str1 + index);
                }
            }
        }
        count = 1;
    }
    return result;
}
