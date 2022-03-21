#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
#define E 1e-7

typedef enum {
  CORRECT_MATRIX = 0,  // корректная матрица
  INCORRECT_MATRIX = 1,  // при ошибках в действиях с матрицами
  IDENTITY_MATRIX = 2,  // единичная матрица
  ZERO_MATRIX = 3       // нулевая матрица
} matrix_type_t;
// Заполнение матрицы в случае типа INCORRECT_MATRIX не определено.

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
  matrix_type_t matrix_type;
} matrix_t;

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t* A);
int s21_eq_matrix(matrix_t* A, matrix_t* B);
matrix_t s21_sum_matrix(matrix_t* A, matrix_t* B);
matrix_t s21_sub_matrix(matrix_t* A, matrix_t* B);
matrix_t s21_mult_number(matrix_t* A, double number);
matrix_t s21_mult_matrix(matrix_t* A, matrix_t* B);
matrix_t s21_transpose(matrix_t* A);
matrix_t s21_calc_complements(matrix_t* A);
double s21_determinant(matrix_t* A);
matrix_t s21_inverse_matrix(matrix_t* A);

// help func
int s21_eq_size(matrix_t* A, matrix_t* B);
int s21_eq_sqr(matrix_t* A);
matrix_t s21_lil_matrix(matrix_t* A, int ip, int jp);
int s21_identity_matrix(matrix_t* A);
int s21_zero_matrix(matrix_t* A);
#endif  // SRC_S21_MATRIX_H_
