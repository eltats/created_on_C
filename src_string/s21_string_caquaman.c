#include "s21_string.h"
void int_to_str(char* str, int number);

void *s21_memset(void* str, int c, s21_size_t n) {
    char *ptr = str;
    while (n) {
        *ptr++ = c;
        n--;
    }
    return str;
}

char *s21_strchr(const char *str, int c) {
    char* ptr = (char*)str;
    int n = s21_strlen(str) + 1;
    while (n && *ptr != (unsigned char)c) {
        ptr++;
        n--;
    }
    return (n == 0) ? S21_NULL : ptr;
}

char *s21_strcpy(char *dest, const char *src) {
    char *ptr = dest;
    for (; *src != '\0'; src++, ptr++) {
        *ptr = *src;
    }
    *ptr = '\0';
    return dest;
}

char *s21_strerror(int errnum) {
    static char result[256];

    char *(errlist[LAST_NUM_ERR]) = { ERR_LIST };
    if (errnum < 0 || errnum >= LAST_NUM_ERR) {
        char *str_errnum = (char*)malloc(sizeof(char) * 1024);
        s21_strcpy(result, UNKNOWN_ERR);
        int_to_str(str_errnum, errnum);
        s21_strcat(result, str_errnum);
        free(str_errnum);
    } else {
        s21_strcpy(result, errlist[errnum]);
    }
    return result;
}

void int_to_str(char* str, int number) {
    if (number < 0) {
        *str++ = '-';
        number *= -1;
    }
    char *tmp = (char*)malloc(sizeof(char) * 1024);
    *tmp = '\0';
    tmp++;
    while (number > 0) {
        *tmp = number % 10 +'0';
        number /= 10;
        tmp++;
    }
    tmp--;
    while (*tmp != '\0') {
        *str = *tmp;
        tmp--;
        str++;
    }
    *str = '\0';
    free(tmp);
}
