#include "s21_calc.h"

double parsing(char *argv) {
    char *output_str = (char *)calloc(MAX_LINE, sizeof(char));
    st_c *stack_oper = NULL;
    int error = SUCCESS;
    int count_bracket_open = 0;
    int count_dot = 0;
    int unar_type = FAILURE;
    double resoult = NAN;
    if (argv[0] == '*' || argv[0] == '/' || argv[0] == '%' || argv[0] == '^') {
        printf("ERROR %c\n", argv[0]);
        error = FAILURE;
    } else {
        for (size_t i = 0; i < strlen(argv) && error; ++i) {
            int a = 0;
            if (s21_check_lexeme(argv[i]) == SUCCESS && error) {
                int boba = 0;
                char *array_number = (char *)calloc(MAX_LINE, sizeof(char));
                for (a = i; s21_check_lexeme(argv[a]) != FAILURE && error;
                     a++) {
                    if (count_dot > 1) {
                        error = FAILURE;
                        printf("ERROR DOT!\n");
                    } else {
                        array_number[boba] = argv[a];
                        ++boba;
                    }
                    if (argv[a] == '.' && error) {
                        count_dot++;
                    }
                }
                if (unar_type == SUCCESS) {
                    strcat(output_str, "0");
                    strcat(output_str, " ");
                    unar_type = FAILURE;
                }
                if (error) {
                    strcat(output_str, array_number);
                    strcat(output_str, " ");
                    free(array_number);
                    count_dot = 0;
                    boba = 0;
                    i = a - 1;
                }
            } else if (argv[i] == '(' && error) {
                stack_oper = s21_push_char(stack_oper, argv[i]);
                count_bracket_open++;
            } else if (s21_check_oper(argv[i]) == 3 && error) {
                if (s21_check_oper(argv[i - 1]) == 0 && argv[i - 2] == '(') {
                    strcat(output_str, "0");
                    strcat(output_str, " ");
                } else if (s21_check_oper(argv[0]) == 0) {
                    strcat(output_str, "0");
                    strcat(output_str, " ");
                }

                char *array_func = (char *)calloc(MAX_LINE, sizeof(char));
                int biba = 0, b = 0;
                for (b = i; argv[b] != '('; ++b) {
                    array_func[biba] = argv[b];
                    ++biba;
                }
                printf("%s\n", array_func);
                s21_check_func_cmp(&stack_oper, array_func);
                i = b - 1;
            } else if ((s21_check_oper(argv[i]) >= -1 &&
                        s21_check_oper(argv[i]) <= 3) &&
                       error) {
                if (s21_check_oper(argv[i]) == 0) {
                    if (s21_check_unar(argv[i - 1], argv[i + 1]) == SUCCESS) {
                        printf("UNAR!\n");
                        unar_type = SUCCESS;
                    }
                }
                int nan = SUCCESS;
                while (stack_oper != NULL && nan) {
                    if (s21_check_oper(stack_oper->simbol) >=
                        s21_check_oper(argv[i])) {
                        s21_check_func(&stack_oper, output_str);
                    } else {
                        nan = FAILURE;
                    }
                }
                stack_oper = s21_push_char(stack_oper, argv[i]);

            } else if (argv[i] == ')' && error && count_bracket_open > 0) {
                while (stack_oper->simbol != '(') {
                    s21_check_func(&stack_oper, output_str);
                }
                s21_pop_char(&stack_oper);
                count_bracket_open--;
            } else {
                error = FAILURE;
                printf("ERROR BRACKET OPEN!\n");
            }
        }
        while (stack_oper != NULL && error) {
            if (stack_oper->simbol == '(') {
                printf("ERROR BRACKET CLOSE!\n");
                error = FAILURE;
            } else {
                s21_check_func(&stack_oper, output_str);
            }
        }
        while (stack_oper != NULL && error) {
            s21_pop_char(&stack_oper);
        }
        if (error) {
            printf("%s\n", output_str);
        }
    }
    if (error) {
        st_d *output_stack = NULL;
        int count_number = 0;
        for (size_t i = 0; i < strlen(output_str); ++i) {
            int pup = 0;
            int j = 0;
            char *array_number = (char *)calloc(MAX_LINE, sizeof(char));
            for (j = i; output_str[j] != ' '; ++j) {
                array_number[pup] = output_str[j];
                pup++;
            }
            pup = 0;
            i = j;
            double number = 0.0;
            char simbol;
            sscanf(array_number, "%c", &simbol);
            if (sscanf(array_number, "%lf", &number) != 0) {
                output_stack = s21_push_double(output_stack, number);
                count_number++;
            }
            s21_arithmetic_operations_func(&output_stack, array_number);
            if (s21_check_simbol(simbol)) {
                if (count_number >= 2) {
                    s21_arithmetic_operations(&output_stack, simbol);
                    count_number -= 1;
                }
            }

            free(array_number);
        }
        resoult = s21_pop_double(&output_stack);
        // printf("%lf\n", resoult);
        free(output_str);
    }
    // free(output_str);
    return resoult;
}
