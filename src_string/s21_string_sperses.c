#include "s21_string.h"
#include <string.h>

void *s21_memchr(const void *str, int c, s21_size_t n) {
    const unsigned char *tmp;
    void *result;
    tmp = str;
    result = S21_NULL;
    while (n != 0) {
        if ((unsigned char)c == *tmp) {
            result = (void*)tmp;
            n = 0;
        } else {
            tmp++;
            n--;
        }
    }
    return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const unsigned char *comp1, *comp2;
    int result;
    comp1 = str1;
    comp2 = str2;
    result = 0;
    while (n != 0) {
        result = *comp1 - *comp2;
        if (result != 0) {
            n = 0;
        } else {
            comp1++;
            comp2++;
            n--;
        }
    }
    return result;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    const unsigned char *str;
    unsigned char *tmp;
    tmp = dest;
    str = src;
    if (dest <= src) {
        while (n != 0) {
            *tmp = *str;
            tmp++;
            str++;
            n--;
        }
    } else {
        tmp += n;
        str += n;
        while (n != 0) {
            tmp--;
            str--;
            *tmp = *str;
            n--;
        }
    }
    return dest;
}

char *s21_strcat(char *dest, const char *src) {
    char *tmp;
    tmp = dest;
    while (*tmp != '\0') {
        tmp++;
    }
    while (*src != '\0') {
        *tmp = *src;
        src++;
        tmp++;
    }
    *tmp = '\0';
    return dest;
}
