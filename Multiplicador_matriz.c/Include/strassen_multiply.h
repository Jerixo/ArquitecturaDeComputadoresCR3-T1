#ifndef STRASSEN_MULTIPLY_H
#define STRASSEN_MULTIPLY_H

void strassen_multiply(double** A, double** B, double** C, int n);

void add_matrix(double** A, double** B, double** result, int n);
void sub_matrix(double** A, double** B, double** result, int n);

#endif
