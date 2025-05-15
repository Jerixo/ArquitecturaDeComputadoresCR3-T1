#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

double** create_matrix(int n);

void free_matrix(double** matrix, int n);
void fill_matrix_random(double** matrix, int n);
void print_matrix(double** matrix, int n);

int compare_matrices(double** A, double** B, int n, double epsilon);

#endif
