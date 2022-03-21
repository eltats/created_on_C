#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *dst = dest;
    for (; *dest != '\0'; dest++) {}
    for (; *src != '\0' && n--; src++, dest++) {
        *dest = *src;
    }
    *dest = '\0';
    return dst;
}

int s21_strcmp(const char *str1, const char *str2) {
    for (; *str1 != '\0' && *str2 != '\0' && *str1 == *str2; str1++, str2++) {}
    return *str1 - *str2;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t n = 0;
    int match = 1;
    for (; *str1 && match; str1++, n++) {
        char *ptr = (char*)str2;
        for (; *ptr && *ptr != *str1; ptr++) {}
        if (!*ptr) {
            match = 0;
            n--;
        }
    }
    return n;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *ret = S21_NULL;
    if (!*needle) ret = (char*)haystack;
    for (; *haystack != '\0' && !ret; haystack++) {
        char *stack = (char*)haystack, *need = (char*)needle;
        for (; *stack && *need && *stack == *need; stack++, need++) {}
        if (!*need) ret = (char*)haystack;
    }
    return ret;
}

char *s21_strtok(char *str, const char *denim) {
    static char *strStatic;
    if (str == S21_NULL) str = strStatic;
    char *leksem = S21_NULL;
    if (str) {
        int delimFound = 0;
        int buff[256] = {0};
        for (; *denim != '\0'; denim++) buff[(int)*denim]++;
        int i = 0;
        for (; str[i]; i++) {
            if (buff[(int)str[i]] < 1 && leksem == S21_NULL) {
                leksem = &str[i];
            }
            if (buff[(int)str[i]] > 0 && !delimFound) {
                str[i] = '\0';
                delimFound = 1;
                i++;
                while (str[i] && buff[(int)str[i]]) i++;
                strStatic = &str[i];
            }
        }
        if (!delimFound) strStatic = S21_NULL;
    }
    return leksem;
}

