#include "s21_string.h"

void* s21_to_upper(const char* str) {
    s21_size_t len = s21_strlen(str) + 1;
    char* ptr = (char*)malloc(sizeof(char) * len);
    s21_memcpy(ptr, str, len);
    char* tmp = ptr;
    for (; *tmp != '\0'; tmp++) {
        if (*tmp >= 'a' && *tmp <= 'z')
            *tmp -= 32;
    }
    return (void*)ptr;
}

void* s21_to_lower(const char* str) {
    s21_size_t len = s21_strlen(str) + 1;
    char* ptr = (char*)malloc(sizeof(char) * len);
    s21_memcpy(ptr, str, len);
    char* tmp = ptr;
    for (; *tmp != '\0'; tmp++) {
        if (*tmp >= 'A' && *tmp <= 'Z')
            *tmp += 32;
    }
    return (void*)ptr;
}

void* s21_insert(const char *src, const char *str, s21_size_t start_index) {
    s21_size_t len1 = s21_strlen(src) + 1;
    s21_size_t len2 = s21_strlen(str);
    char* ptr = (char*)malloc(sizeof(char) * (len1 + len2));
    s21_memcpy(ptr, src, start_index);
    s21_memcpy(ptr + start_index, str, len2);
    s21_memcpy(ptr + start_index + len2, src + start_index, len1 - start_index);
    return (void*)ptr;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *trims;
    if (trim_chars == S21_NULL) {
        trims = " ";
    } else {
        trims = (char*)trim_chars;
    }
    s21_size_t moveBeg = s21_strspn(src, trims);
    s21_size_t moveBack = (s21_strlen(src) == 0) ? 0 : s21_strlen(src) - 1;
    for (; moveBack > 0 && s21_strchr(trims, src[moveBack]) != NULL; moveBack--) {}
    moveBack++;
    char *res = (char*)malloc(sizeof(char) * (moveBack - moveBeg + 1));
    for (size_t j = 0; j < moveBack - moveBeg ; j++) {
        res[j] = src[moveBeg + j];
    }
    res[moveBack - moveBeg] = '\0';
    return (void*)res;
}
