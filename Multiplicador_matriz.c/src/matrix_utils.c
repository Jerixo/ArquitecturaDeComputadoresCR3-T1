
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../include/matrix_utils.h"

double** create_matrix(int n) {
    double** matrix = (double**) malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*) malloc(n * sizeof(double));
    }
    return matrix;
}

void free_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void fill_matrix_random(double** matrix, int n) {
    srand((unsigned int) time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10; 
        }
    }
}

void print_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int compare_matrices(double** A, double** B, int n, double epsilon) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(A[i][j] - B[i][j]) > epsilon) {
                return 0; 
            }
        }
    }
    return 1; 
}
