#include "s21_calc.h"

// help func
int s21_check_lexeme(char number) {
    return (number >= '0' && number <= '9') || number == '.' ? SUCCESS
                                                             : FAILURE;
}

int s21_check_oper(char simbol) {
    int result = -2;
    if (simbol == COS || simbol == SIN || simbol == TAN || simbol == ACOS ||
        simbol == ASIN || simbol == ATAN || simbol == SQRT || simbol == LN ||
        simbol == LOG || simbol == 'a') {
        result = FUNC_CHAR;
    } else if (simbol == '^') {
        result = MEDIUM_CHAR;
    } else if (simbol == '*' || simbol == '/' || simbol == '%') {
        result = EASY_CHAR;
    } else if (simbol == '+' || simbol == '-') {
        result = LOW_CHAR;
    } else if (simbol == '(') {
        result = VERY_LOW_CHAR;
    } else {
        result = -2;
    }
    return result;
}

void s21_check_func(st_c **stack_oper, char *output_str) {
    if ((*stack_oper)->simbol == 'c') {
        strcat(output_str, "cos");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 's') {
        strcat(output_str, "sin");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 't') {
        strcat(output_str, "tan");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 'C') {
        strcat(output_str, "acos");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 'S') {
        strcat(output_str, "asin");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 'T') {
        strcat(output_str, "atan");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 'q') {
        strcat(output_str, "sqrt");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 'l') {
        strcat(output_str, "ln");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else if ((*stack_oper)->simbol == 'L') {
        strcat(output_str, "log");
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    } else {
        strcat(output_str, &(*stack_oper)->simbol);
        strcat(output_str, " ");
        s21_pop_char(stack_oper);
    }
}

void s21_check_func_cmp(st_c **stack_oper, char *output_str) {
    if (strcmp(output_str, "cos") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 'c');
        free(output_str);
    } else if (strcmp(output_str, "sin") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 's');
        free(output_str);
    } else if (strcmp(output_str, "tan") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 't');
        free(output_str);
    } else if (strcmp(output_str, "acos") == 0) {
        printf("ATAN!\n");
        *stack_oper = s21_push_char(*stack_oper, 'C');
        free(output_str);
    } else if (strcmp(output_str, "asin") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 'S');
        free(output_str);
    } else if (strcmp(output_str, "atan") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 'T');
        free(output_str);
    } else if (strcmp(output_str, "sqrt") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 'q');
        free(output_str);
    } else if (strcmp(output_str, "ln") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 'l');
        free(output_str);
    } else if (strcmp(output_str, "log") == 0) {
        *stack_oper = s21_push_char(*stack_oper, 'L');
        free(output_str);
    }
}
int s21_check_unar(char previous, char next) {
    int resoult = FAILURE;
    if (s21_check_lexeme(next) == SUCCESS) {
        if (s21_check_lexeme(previous) == FAILURE) {
            if (previous != ')') {
                resoult = SUCCESS;
            }
        }
    }
    return resoult;
}

int s21_check_simbol(char simbol) {
    int error = FAILURE;
    if (simbol == '+' || simbol == '-' || simbol == '^' || simbol == '/' ||
        simbol == '*') {
        error = SUCCESS;
    }
    return error;
}
void s21_arithmetic_operations(st_d **stack_oper, char simbol) {
    if (simbol == '+') {
        double b = s21_pop_double(stack_oper);
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, a + b);
    } else if (simbol == '-') {
        double b = s21_pop_double(stack_oper);
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, a - b);
    } else if (simbol == '*') {
        double b = s21_pop_double(stack_oper);
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, a * b);
    } else if (simbol == '/') {
        double b = s21_pop_double(stack_oper);
        double a = s21_pop_double(stack_oper);
        if (b != 0) {
            *stack_oper = s21_push_double(*stack_oper, a / b);
        } else {
            printf("NONONONO! DIV 0\n");
        }
    } else if (simbol == '^') {
        double b = s21_pop_double(stack_oper);
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, powl(a, b));
    } else if (simbol == '%') {
        double b = s21_pop_double(stack_oper);
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, fmod(a, b));
    }
}

void s21_arithmetic_operations_func(st_d **stack_oper, char *func) {
    if (strcmp(func, "cos") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, cos(a));
    } else if (strcmp(func, "sin") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, sin(a));
    } else if (strcmp(func, "tan") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, tan(a));
    } else if (strcmp(func, "acos") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, acos(a));
    } else if (strcmp(func, "asin") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, asin(a));
    } else if (strcmp(func, "atan") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, atan(a));
    } else if (strcmp(func, "sqrt") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, sqrt(a));
    } else if (strcmp(func, "ln") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, log(a));
    } else if (strcmp(func, "log") == 0) {
        double a = s21_pop_double(stack_oper);
        *stack_oper = s21_push_double(*stack_oper, log10(a));
    }
}