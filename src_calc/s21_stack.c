#include "s21_stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// char stack
st_c *s21_push_char(st_c *ptr, char ham) {
    st_c *temp = (st_c *)malloc(sizeof(st_c));
    temp->simbol = ham;
    temp->next = ptr;
    return temp;
}
void s21_print_stuct_char(st_c *stack) {
    int i = 0;
    while (stack != NULL) {
        printf("stack_ostatok[%d] = [%c]\n", i, stack->simbol);
        stack = stack->next;
        ++i;
    }
}
char s21_pop_char(st_c **stack) {
    char simbol;
    if (*stack != NULL) {
        simbol = (*stack)->simbol;
        st_c *temp = (*stack);
        (*stack) = (*stack)->next;
        free(temp);
    }
    return simbol;
}
// double stack
st_d *s21_push_double(st_d *ptr, double ham) {
    st_d *temp = (st_d *)malloc(sizeof(st_d));
    temp->number = ham;
    temp->next = ptr;
    return temp;
}
void s21_print_stuct_double(st_d *stack) {
    int i = 0;
    while (stack != NULL) {
        printf("stack_ostatok[%d] = [%lf]\n", i, stack->number);
        stack = stack->next;
        ++i;
    }
}
double s21_pop_double(st_d **stack) {
    double number;
    if (*stack != NULL) {
        number = (*stack)->number;
        st_d *temp = (*stack);
        (*stack) = (*stack)->next;
        free(temp);
    }
    return number;
}