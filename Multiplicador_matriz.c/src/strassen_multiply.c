#include <stdlib.h>
#include "../include/strassen_multiply.h"
#include "../include/matrix_utils.h"

void add_matrix(double** A, double** B, double** result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(double** A, double** B, double** result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
}

void strassen_multiply(double** A, double** B, double** C, int n) {
    if (n <= 64) { 
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                C[i][j] = 0.0;
                for (int k = 0; k < n; k++)
                    C[i][j] += A[i][k] * B[k][j];
            }
        return;
    }

    int newSize = n / 2;

    double **A11 = create_matrix(newSize), **A12 = create_matrix(newSize);
    double **A21 = create_matrix(newSize), **A22 = create_matrix(newSize);
    double **B11 = create_matrix(newSize), **B12 = create_matrix(newSize);
    double **B21 = create_matrix(newSize), **B22 = create_matrix(newSize);
    double **C11 = create_matrix(newSize), **C12 = create_matrix(newSize);
    double **C21 = create_matrix(newSize), **C22 = create_matrix(newSize);

    double **M1 = create_matrix(newSize), **M2 = create_matrix(newSize);
    double **M3 = create_matrix(newSize), **M4 = create_matrix(newSize);
    double **M5 = create_matrix(newSize), **M6 = create_matrix(newSize);
    double **M7 = create_matrix(newSize);

    double **T1 = create_matrix(newSize), **T2 = create_matrix(newSize);


    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    add_matrix(A11, A22, T1, newSize);
    add_matrix(B11, B22, T2, newSize);
    strassen_multiply(T1, T2, M1, newSize);

    // M2 = (A21 + A22)B11
    add_matrix(A21, A22, T1, newSize);
    strassen_multiply(T1, B11, M2, newSize);

    // M3 = A11(B12 - B22)
    sub_matrix(B12, B22, T1, newSize);
    strassen_multiply(A11, T1, M3, newSize);

    // M4 = A22(B21 - B11)
    sub_matrix(B21, B11, T1, newSize);
    strassen_multiply(A22, T1, M4, newSize);

    // M5 = (A11 + A12)B22
    add_matrix(A11, A12, T1, newSize);
    strassen_multiply(T1, B22, M5, newSize);

    // M6 = (A21 - A11)(B11 + B12)
    sub_matrix(A21, A11, T1, newSize);
    add_matrix(B11, B12, T2, newSize);
    strassen_multiply(T1, T2, M6, newSize);

    // M7 = (A12 - A22)(B21 + B22)
    sub_matrix(A12, A22, T1, newSize);
    add_matrix(B21, B22, T2, newSize);
    strassen_multiply(T1, T2, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    add_matrix(M1, M4, T1, newSize);
    sub_matrix(T1, M5, T2, newSize);
    add_matrix(T2, M7, C11, newSize);

    // C12 = M3 + M5
    add_matrix(M3, M5, C12, newSize);

    // C21 = M2 + M4
    add_matrix(M2, M4, C21, newSize);

    // C22 = M1 - M2 + M3 + M6
    sub_matrix(M1, M2, T1, newSize);
    add_matrix(T1, M3, T2, newSize);
    add_matrix(T2, M6, C22, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Liberar memoria
    free_matrix(A11, newSize); free_matrix(A12, newSize);
    free_matrix(A21, newSize); free_matrix(A22, newSize);
    free_matrix(B11, newSize); free_matrix(B12, newSize);
    free_matrix(B21, newSize); free_matrix(B22, newSize);
    free_matrix(C11, newSize); free_matrix(C12, newSize);
    free_matrix(C21, newSize); free_matrix(C22, newSize);
    free_matrix(M1, newSize); free_matrix(M2, newSize);
    free_matrix(M3, newSize); free_matrix(M4, newSize);
    free_matrix(M5, newSize); free_matrix(M6, newSize);
    free_matrix(M7, newSize); free_matrix(T1, newSize); free_matrix(T2, newSize);
}
