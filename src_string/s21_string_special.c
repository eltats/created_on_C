#include "s21_string.h"
#include <stdlib.h>

#define INT_MINIMUM -9223372036854775807
// #define INT_MINIMUM -2147483647
#define SPECIFIERS_MAXIMUM_SIZE 5
#define MAX_STRING_LEN 1024

const char *parser(int *result, const char *point);
const char *flags_parser(const char *point, int *flags);
const char *width_parser(const char *point, int *width);
const char *precision_parser(const char *point, int *precision);
const char *lenght_parser(const char *point, int *length);
const char *specifiers_parser(const char *point, int *specifier);
char *specifiers_print(int *buffer, char *str, va_list *varg, char *start, int *error);
void notation_convert(unsigned int nt, va_list *varg, int length, int flag, char *str);
void unotation_convert(unsigned int nt, va_list *varg, int length, int capital,
                       char *str, unsigned long int cnum, int hashtag);
void dig_move(s21_wchar_t num, int depth, char *str);
void width_formater(int width, char *string, int justify, char space);
void precision_formater(int precision, char *string);
char *string_print(char *to, char *from);
const char *read_number_from_str(const char *str, int *num);
void split_to_whole_and_decimal(long int *whole, long int *decimal, long double num, int precision);
int fetch_to_scientific(long double *num);
void calculate_precision_values_for_g(long int whole, long int decimal,
                                      int *count, int *tmp, int precision, int hashflag);
void set_output_format(char *output, char *spec, const int *buffer);
void print_c(char *string, va_list *varg, int *error);
void print_d(char *string, int *buffer, va_list *varg);
void print_e(char *string, int *buffer, va_list *varg);
void print_f(char *string, int *buffer, va_list *varg);
void print_g(char *string, int *buffer, va_list *varg);
void print_o(char *string, int *buffer, va_list *varg);
void print_s(char *string, int *buffer, va_list *varg, int *error);
void print_u(char *string, int *buffer, va_list *varg);
void print_x(char *string, int *buffer, va_list *varg);
void print_p(char *string, int *buffer, va_list *varg);
void print_n(const char *str, const char *start, va_list *varg);
void print_percent(char *string);

int s21_sprintf(char *str, const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    int buffer[SPECIFIERS_MAXIMUM_SIZE];
    char *start = str;
    int count = 0;
    int error = 0;
    while (*format != '\0') {
        if (*format == '%') {
            format = parser(buffer, format);
            str = specifiers_print(buffer, str, &argptr, start, &error);
        } else {
            *str = *format;
            str++;
            format++;
        }
    }
    if (error == 1) {
        count = -1;
        *start = '\0';
    } else {
        count = str - start;
        *str = '\0';
    }
    va_end(argptr);
    return count;
}

const char *parser(int *result, const char *point) {
    point++;
    const char * tmp = S21_NULL;
    *result = 0;
    while (tmp != point) {
        tmp = point;
        point = flags_parser(point, result);
    }
    point = width_parser(point, result + 1);
    point = precision_parser(point, result + 2);
    point = lenght_parser(point, result + 3);
    point = specifiers_parser(point, result + 4);
    return point;
}

const char *flags_parser(const char *point, int *flags) {
    int save = 1;
    if (*point == '-') {
        *flags |= 16;
    } else if (*point == '+') {
        *flags |= 8;
    } else if (*point == ' ') {
        *flags |= 4;
    } else if (*point == '#') {
        *flags |= 2;
    } else if (*point == '0') {
        *flags |= 1;
    } else {
        save = 0;
    }
    if (save) point++;
    return point;
}

const char *width_parser(const char *point, int *width) {
    *width = 0;
    if (point != S21_NULL) {
        if (*point >= '0' && *point <= '9') {
            point = read_number_from_str(point, width);
        } else if (*point == '*') {
            *width = -1;
            point++;
        } else {}
    }
    return point;
}

const char *precision_parser(const char *point, int *precision) {
    *precision = -2;
    if (*point == '.') {
        point++;
        *precision = 0;
        if (*point >= '0' && *point <= '9') {
            point = read_number_from_str(point, precision);
        } else if (*point == '*') {
            *precision = -1;
            point++;
        } else {}
    }
    return point;
}

const char *lenght_parser(const char *point, int *length) {
    *length = 0;
    if (*point == 'h') {
        *length = 1;
    } else if (*point == 'l') {
        *length = 2;
    } else if (*point == 'L') {
        *length = 3;
    } else {}
    if (*length != 0) {
        point++;
    }
    return point;
}

const char *specifiers_parser(const char *point, int *specifier) {
    *specifier = 0;
    if (*point == 'c') {
        *specifier = 1;
    } else if (*point == 'd') {
        *specifier = 2;
    } else if (*point == 'i') {
        *specifier = 3;
    } else if (*point == 'e') {
        *specifier = 4;
    } else if (*point == 'E') {
        *specifier = 5;
    } else if (*point == 'f') {
        *specifier = 6;
    } else if (*point == 'g') {
        *specifier = 7;
    } else if (*point == 'G') {
        *specifier = 8;
    } else if (*point == 'o') {
        *specifier = 9;
    } else if (*point == 's') {
        *specifier = 10;
    } else if (*point == 'u') {
        *specifier = 11;
    } else if (*point == 'x') {
        *specifier = 12;
    } else if (*point == 'X') {
        *specifier = 13;
    } else if (*point == 'p') {
        *specifier = 14;
    } else if (*point == 'n') {
        *specifier = 15;
    } else if (*point == '%') {
        *specifier = 16;
    } else {}
    if (*specifier != 0) {
        point++;
    }
    return point;
}

char *specifiers_print(int *buffer, char *str, va_list *varg, char *start, int *error) {
    int justify = 0;  // == 0 - right-justify, == 1 - left-justify
    char space = ' ';  // character to fill spaces when width specified
    if (*(buffer + 1) == -1) {
        *(buffer + 1) = va_arg(*varg, int);
    }
    if (*(buffer + 2) == -1) {
        *(buffer + 2) = va_arg(*varg, int);
    }
    if (*buffer & 16) {
        justify = 1;
    }
    if ((*buffer & 1) && (justify == 0)
         && (*(buffer + 2) == -2 || (*(buffer + 4) != 2 && *(buffer + 4) != 3))) {
        space = '0';
    }
    char *string = (char*)malloc(MAX_STRING_LEN * sizeof(char));
    if (*(buffer + 4) == 1) {  // %c
        print_c(string, varg, error);
    } else if (*(buffer + 4) == 2 || *(buffer + 4) == 3) {  // %d or %i
        print_d(string, buffer, varg);
    } else if (*(buffer + 4) == 4 || *(buffer + 4) == 5) {  // %e or %E
        print_e(string, buffer, varg);
    } else if (*(buffer + 4) == 6) {  // %f
        print_f(string, buffer, varg);
    } else if (*(buffer + 4) == 7 || *(buffer + 4) == 8) {  // %g or %G
        print_g(string, buffer, varg);
    } else if (*(buffer + 4) == 9) {  // %o
        print_o(string, buffer, varg);
    } else if (*(buffer + 4) == 10) {  // %s
        print_s(string, buffer, varg, error);
    } else if (*(buffer + 4) == 11) {  // %u
        print_u(string, buffer, varg);
    } else if (*(buffer + 4) == 12 || *(buffer + 4) == 13) {  // %x or %X
        print_x(string, buffer, varg);
    } else if (*(buffer + 4) == 14) {  // %p
        print_p(string, buffer, varg);
    } else if (*(buffer + 4) == 15) {  // %n
        print_n(str, start, varg);
    } else if (*(buffer + 4) == 16) {  // %%
        print_percent(string);
    } else {}
    if (*(buffer + 4) != 15) {
        width_formater(*(buffer + 1), string, justify, space);
        str = string_print(str, string);
    }
    free(string);
    return str;
}

void notation_convert(unsigned int nt, va_list *varg, int length, int flag, char *str) {
    long int num = 0;
    if (length == 0) {
        num = va_arg(*varg, int);
    } else if (length == 1) {
        num = (short int)va_arg(*varg, int);
    } else if (length == 2) {
        num = va_arg(*varg, long int);
    }
    int minmax = 0;
    if (num < 0) {
        *str++ = '-';
        if (num < INT_MINIMUM) {
            unsigned long int unum = num * -1;
            unotation_convert(nt, varg, length, 0, str, unum, 0);
            minmax++;
        } else {
            num *= -1;
        }
    } else if (flag & 8) {
        *str++ = '+';
    } else if (flag & 4) {
        *str++ = ' ';
    } else {}
    if (minmax == 0) {
        *str = '\0';
        int depth = 1;
        if (num == 0) {
            depth++;
            dig_move('0', depth, str);
        } else {
            while (num > 0) {
                int tmp = 0;
                tmp = num % nt + '0';
                num /= nt;
                depth++;
                dig_move(tmp, depth, str);
            }
        }
    }
}

void unotation_convert(unsigned int nt, va_list *varg, int length,
                        int capital, char *str, unsigned long int cnum, int hashtag) {
    unsigned long int num = 0;
    if (cnum != 0) {
        num = cnum;
    } else {
        if (length == 0) {
            num = va_arg(*varg, unsigned int);
        } else if (length == 1) {
            num = (unsigned short int)va_arg(*varg, int);
        } else if (length == 2) {
            num = va_arg(*varg, unsigned long int);
        }
    }
    int depth = 1;
    if (hashtag == 1 && num != 0) {
        if (nt == 8) {
            *str++ = '0';
            depth++;
        } else if (nt == 16) {
            *str++ = '0';
            if (capital == 0) {
                *str++ = 'x';
            } else if (capital == 1) {
                *str++ = 'X';
            }
            depth += 2;
        }
    }
    *str = '\0';
    if (num == 0) {
        depth++;
        dig_move('0', depth, str);
    } else {
        char num_symb = 'a';
        if (capital == 1) {
            num_symb = 'A';
        }
        if (nt != 0) {
            while (num > 0) {
                int tmp = 0;
                tmp = num % nt;
                if (tmp >= 0 && tmp < 10) {
                    tmp += '0';
                } else {
                    tmp = tmp % 10 + num_symb;
                }
                num /= nt;
                depth++;
                dig_move(tmp, depth, str);
            }
        }
    }
}

void dig_move(s21_wchar_t num, int depth, char *str) {
    if (depth > 0) {
        s21_wchar_t tmp = *str;
        *str = num;
        depth--;
        dig_move(tmp, depth, str + 1);
    }
}

void width_formater(int width, char *string, int justify, char space) {
    char *save = string;
    while (*string != '\0') {
        string++;
    }
    int count = string - save;
    if (justify) {
        save = string;
    }
    int skip = 0;
    if (*save == '+' || *save == '-') {
        skip = 1;
    } else if (*(save + 1) == 'x' || *(save + 1) == 'X') {
        skip = 2;
    } else {}
    if (space == '0') save += skip;
    if (count < width) {
        while (count++ != width) {
            dig_move(space, count, save);
            string++;
        }
    }
    *string = '\0';
}

void precision_formater(int precision, char *string) {
    char *save = string;
    if (precision == -2) {
        precision = 1;
    }
    if (*string == '0' && precision == 0) {
        *string = '\0';
    } else {
        if (*string == '-' || *string == '+') {
            save++;
        } else if (*(string + 1) == 'x' || *(string + 1) == 'X') {
            save += 2;
        } else {}
        while (*string != '\0') {
            string++;
        }
        int count = string - save;
        if (count < precision) {
            while (count++ != precision) {
                dig_move('0', count, save);
                string++;
            }
        }
        *string = '\0';
    }
}

char *string_print(char *to, char *from) {
    while (*from != '\0') {
        *to = *from;
        to++;
        from++;
    }
    return to;
}

const char *read_number_from_str(const char *str, int *num) {
    while (*str >= '0' && *str <= '9') {
        *num *= 10;
        *num += *str - '0';
        str++;
    }
    return str;
}

void split_to_whole_and_decimal(long int *whole, long int *decimal, long double num, int precision) {
    int sign = 1;
    if (num < 0) {
        num *= -1;
        sign = -1;
    }
    long double save = num;
    num = ((num + 0.05) * 100) / 100;  // round
    *whole = (long int)num;
    save -= *whole;
    (*whole) *= sign;
    for (int i = 0; i < precision; i++, save *= 10.0) {}
    if (num < 0.0) save *= -1.0;
    save = ((save + 0.05) * 100) / 100;  // round
    *decimal = (long int)save;
}

int fetch_to_scientific(long double *num) {
    int count = 0;
    if (*num != 0.0) {
        if (*num > 1.0 || *num < -1.0) {
            for (; *num >= 10.0 || *num <= -10.0; *num /= 10.0, count++) {}
        } else if (*num < 0.1 && *num > -0.1) {
            for (; *num <= 0.9 && *num >= -0.9; *num *= 10.0, count--) {}
        } else {}
    }
    return count;
}

void calculate_precision_values_for_g(long int whole, long int decimal,
                                      int *count, int *tmp, int precision, int hashflag) {
    while (whole != 0) {
        whole /= 10;
        (*count)++;;
    }
    if ((precision - *count) > 0 && !(hashflag)) {
        for (int i = 0; i < *count; i++, decimal /= 10) {}
        if (decimal == 0) {
            *tmp = precision - *count;
        } else {
            while ((decimal % 10) == 0 && decimal != 0) {
                (*tmp)++;
                decimal /= 10;
            }
        }
    }
}

void set_output_format(char *output, char *spec, const int *buffer) {
    char *flags = (char*)malloc(5 * sizeof(char));
    char *t = flags;
    if (*buffer & 2) *t++ = '#';
    if (*buffer & 4) *t++ = ' ';
    if (*buffer & 8) *t++ = '+';
    *t = '\0';
    s21_sprintf(output, "%%%s%s", flags, spec);
    free(flags);
}

void print_c(char *string, va_list *varg, int *error) {
    int count = 0;
    s21_wchar_t arg = va_arg(*varg, s21_wchar_t);
    count++;
    *string = '\0';
    count++;
    dig_move(arg, count, string);
    if (arg > 255 || arg < 0) *error = 1;
}

void print_d(char *string, int *buffer, va_list *varg) {
    notation_convert(10, varg, *(buffer + 3), *buffer, string);
    precision_formater(*(buffer + 2), string);
}

void print_e(char *string, int *buffer, va_list *varg) {
    char exp_symb = 'e';
    if (*(buffer + 4) == 5) exp_symb = 'E';
    long double arg;
    if (*(buffer + 3) == 3) {
        arg = va_arg(*varg, long double);
    } else {
        arg = va_arg(*varg, double);
    }
    int count = fetch_to_scientific(&arg);
    int precision = *(buffer + 2);
    if (precision == -2) precision = 6;
    char *output = (char*)malloc(MAX_STRING_LEN * sizeof(char));
    char *spec = ".*Lf%c%+.2d";
    set_output_format(output, spec, buffer);
    s21_sprintf(string, output, precision, arg, exp_symb, count);
    free(output);
}

void print_f(char *string, int *buffer, va_list *varg) {
    long double arg;
    if (*(buffer + 3) == 3) {
        arg = va_arg(*varg, long double);
    } else {
        arg = va_arg(*varg, double);
    }
    long int whole = 0;
    long int decimal = 0;
    int precision = 6;
    if (*(buffer + 2) != -2) precision = *(buffer + 2);
    split_to_whole_and_decimal(&whole, &decimal, arg, precision);
    char *output = (char*)malloc(MAX_STRING_LEN * sizeof(char));
    char *spec;
    if (precision == 0) {
        if (*buffer & 2) {
            spec = "ld.";
        } else {
            spec = "ld";
        }
    } else {
        spec = "ld.%.*lu";
    }
    *output = '\0';
    if (arg < 0 && whole == 0) *output++ = '-';
    set_output_format(output, spec, buffer);
    if (arg < 0 && whole == 0) output--;
    s21_sprintf(string, output, whole, precision, decimal);
    free(output);
}

void print_g(char *string, int *buffer, va_list *varg) {
    long double arg;
    if (*(buffer + 3) == 3) {
        arg = va_arg(*varg, long double);
    } else {
        arg = va_arg(*varg, double);
    }
    char symb = 'f';
    long double save = arg;
    long int up_lim = 10;
    long double low_lim = 10;
    int precision = 6;
    if (*(buffer + 2) != -2) precision = *(buffer + 2);
    for (int i = 1; i < precision; i++) {
        up_lim *= 10;
        low_lim /= 10;
    }
    if ((int)arg >= up_lim || (arg <= low_lim && arg >= -1 * low_lim) || (int)arg <= -1 * up_lim) {
        fetch_to_scientific(&arg);
        if (*(buffer + 4) == 8) {
            symb = 'E';
        } else {
            symb = 'e';
        }
    }
    long int whole = 0;
    long int decimal = 0;
    split_to_whole_and_decimal(&whole, &decimal, arg, precision);
    int count = 0;
    int tmp = 0;
    calculate_precision_values_for_g(whole, decimal, &count, &tmp, precision, *buffer & 2);
    precision -= count + tmp;
    if (precision < 0) precision = 0;
    char *output = (char*)malloc(MAX_STRING_LEN * sizeof(char));
    char *spec = (char*)malloc(MAX_STRING_LEN * sizeof(char));
    s21_sprintf(spec, ".*L%c", symb);
    set_output_format(output, spec, buffer);
    s21_sprintf(string, output, precision, save);
    free(output);
    free(spec);
}

void print_o(char *string, int *buffer, va_list *varg) {
    int tag = 0;
    if (*buffer & 2) tag = 1;
    unotation_convert(8, varg, *(buffer + 3), 0, string, 0, tag);
    if (tag == 1 && *(buffer + 2) == 0) *(buffer + 2) += 1;
    precision_formater(*(buffer + 2), string);
}

void print_s(char *string, int *buffer, va_list *varg, int *error) {
    if (*(buffer + 3) == 2) {
        s21_wchar_t *argw = va_arg(*varg, s21_wchar_t*);
        for (int i = 0; *argw != 0  && i != *(buffer + 2); i++) {
            if (*argw > 255 || *argw < -1) *error = 1;
            *string++ = *argw++;
        }
    } else {
        char *argc = va_arg(*varg, char*);
        for (int i = 0; *argc != '\0' && i != *(buffer + 2); i++) {
            if ((int)*argc > 255 || (int)*argc < -1) *error = 1;
            *string++ = *argc++;
        }
    }
    *string = '\0';
}

void print_u(char *string, int *buffer, va_list *varg) {
    int tag = 0;
    if (*buffer & 2) tag = 1;
    unotation_convert(10, varg, *(buffer + 3), 0, string, 0, tag);
    precision_formater(*(buffer + 2), string);
}

void print_x(char *string, int *buffer, va_list *varg) {
    int capitals = 0;
    if (*(buffer + 4) == 13) {
        capitals++;
    }
    int tag = 0;
    if (*buffer & 2) tag = 1;
    unotation_convert(16, varg, *(buffer + 3), capitals, string, 0, tag);
    precision_formater(*(buffer + 2), string);
}

void print_p(char *string, int *buffer, va_list *varg) {
    unsigned long int arg = va_arg(*varg, unsigned long int);
    int width = 14;
    int precision = 12;
    if (*(buffer + 2) != -2) {
        precision = *(buffer + 2);
    }
    if (*(buffer + 1) != 0) {
        width = *(buffer + 1);
    }
    s21_sprintf(string, "%#*.*lx", width, precision, arg);
}

void print_n(const char *str, const char *start, va_list *varg) {
    int *arg = va_arg(*varg, int*);
    int count = 0;
    while (str-- != start) {
        count++;
    }
    *arg = count;
}


void print_percent(char *string) {
    *string = '%';
    *(string + 1) = '\0';
}
