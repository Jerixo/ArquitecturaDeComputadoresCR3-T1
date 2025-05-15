#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <immintrin.h>  // AVX intrinsics

// Crear matriz contigua n x n
double* crear_matriz(int n) {
    double* matriz = (double*)aligned_alloc(32, n * n * sizeof(double));
    if (!matriz) {
        fprintf(stderr, "Error malloc\n");
        exit(EXIT_FAILURE);
    }
    return matriz;
}

void liberar_matriz(double* matriz) {
    free(matriz);
}

void generar_aleatoria(double* M, int n) {
    for (int i = 0; i < n * n; ++i)
        M[i] = (double)rand() / RAND_MAX;
}

static inline double get(double* M, int n, int i, int j) {
    return M[i * n + j];
}

static inline void set(double* M, int n, int i, int j, double val) {
    M[i * n + j] = val;
}

size_t getCurrentRSS() {
    FILE* f = fopen("/proc/self/status", "r");
    if (!f) return 0;
    char line[256];
    size_t rss = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line + 6, "%zu", &rss);
            break;
        }
    }
    fclose(f);
    return rss; // KB
}

double diff_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;
}

void naive_multiply_avx(double* A, double* B, double* C, int n) {
    memset(C, 0, n * n * sizeof(double));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            __m256d a_vec = _mm256_set1_pd(A[i * n + k]);
            int j;
            for (j = 0; j <= n - 4; j += 4) {
                __m256d b_vec = _mm256_loadu_pd(&B[k * n + j]);
                __m256d c_vec = _mm256_loadu_pd(&C[i * n + j]);
                __m256d mul = _mm256_mul_pd(a_vec, b_vec);
                c_vec = _mm256_add_pd(c_vec, mul);
                _mm256_storeu_pd(&C[i * n + j], c_vec);
            }
            for (; j < n; ++j) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void sumar(double* A, double* B, double* R, int n) {
    for (int i = 0; i < n * n; ++i)
        R[i] = A[i] + B[i];
}

void restar(double* A, double* B, double* R, int n) {
    for (int i = 0; i < n * n; ++i)
        R[i] = A[i] - B[i];
}

void split(double* M, double* M11, double* M12, double* M21, double* M22, int n) {
    int mid = n / 2;
    for (int i = 0; i < mid; ++i) {
        memcpy(M11 + i * mid, M + i * n, mid * sizeof(double));
        memcpy(M12 + i * mid, M + i * n + mid, mid * sizeof(double));
        memcpy(M21 + i * mid, M + (i + mid) * n, mid * sizeof(double));
        memcpy(M22 + i * mid, M + (i + mid) * n + mid, mid * sizeof(double));
    }
}

void join(double* C11, double* C12, double* C21, double* C22, double* C, int n) {
    int mid = n / 2;
    for (int i = 0; i < mid; ++i) {
        memcpy(C + i * n, C11 + i * mid, mid * sizeof(double));
        memcpy(C + i * n + mid, C12 + i * mid, mid * sizeof(double));
        memcpy(C + (i + mid) * n, C21 + i * mid, mid * sizeof(double));
        memcpy(C + (i + mid) * n + mid, C22 + i * mid, mid * sizeof(double));
    }
}

void strassen_recursive(double* A, double* B, double* C, int n) {
    if (n <= 64) {
        naive_multiply_avx(A, B, C, n);
        return;
    }
    int mid = n / 2;
    size_t size = mid * mid * sizeof(double);

    double *A11 = aligned_alloc(32, size);
    double *A12 = aligned_alloc(32, size);
    double *A21 = aligned_alloc(32, size);
    double *A22 = aligned_alloc(32, size);
    double *B11 = aligned_alloc(32, size);
    double *B12 = aligned_alloc(32, size);
    double *B21 = aligned_alloc(32, size);
    double *B22 = aligned_alloc(32, size);

    double *M1 = aligned_alloc(32, size);
    double *M2 = aligned_alloc(32, size);
    double *M3 = aligned_alloc(32, size);
    double *M4 = aligned_alloc(32, size);
    double *M5 = aligned_alloc(32, size);
    double *M6 = aligned_alloc(32, size);
    double *M7 = aligned_alloc(32, size);

    double *T1 = aligned_alloc(32, size);
    double *T2 = aligned_alloc(32, size);

    split(A, A11, A12, A21, A22, n);
    split(B, B11, B12, B21, B22, n);

    sumar(A11, A22, T1, mid);
    sumar(B11, B22, T2, mid);
    strassen_recursive(T1, T2, M1, mid);

    sumar(A21, A22, T1, mid);
    strassen_recursive(T1, B11, M2, mid);

    restar(B12, B22, T2, mid);
    strassen_recursive(A11, T2, M3, mid);

    restar(B21, B11, T2, mid);
    strassen_recursive(A22, T2, M4, mid);

    sumar(A11, A12, T1, mid);
    strassen_recursive(T1, B22, M5, mid);

    restar(A21, A11, T1, mid);
    sumar(B11, B12, T2, mid);
    strassen_recursive(T1, T2, M6, mid);

    restar(A12, A22, T1, mid);
    sumar(B21, B22, T2, mid);
    strassen_recursive(T1, T2, M7, mid);

    sumar(M1, M4, T1, mid);
    restar(T1, M5, T2, mid);
    sumar(T2, M7, C, mid);

    sumar(M3, M5, C + mid, mid);
    sumar(M2, M4, C + mid * n, mid);

    restar(M1, M2, T1, mid);
    sumar(T1, M3, T2, mid);
    sumar(T2, M6, C + mid * n + mid, mid);

    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(M1); free(M2); free(M3); free(M4);
    free(M5); free(M6); free(M7);
    free(T1); free(T2);
}

int next_power_of_two(int x) {
    int p = 1;
    while (p < x) p <<= 1;
    return p;
}

void pad_matrix(double* M, double* P, int old_n, int new_n) {
    memset(P, 0, new_n * new_n * sizeof(double));
    for (int i = 0; i < old_n; ++i)
        memcpy(P + i * new_n, M + i * old_n, old_n * sizeof(double));
}

void strassen(double* A, int a_n, double* B, int b_n, double* C, int c_n) {
    int max_n = a_n > b_n ? a_n : b_n;
    max_n = max_n > c_n ? max_n : c_n;
    int s = next_power_of_two(max_n);

    double* A_pad = crear_matriz(s);
    double* B_pad = crear_matriz(s);
    double* C_pad = crear_matriz(s);

    pad_matrix(A, A_pad, a_n, s);
    pad_matrix(B, B_pad, b_n, s);

    strassen_recursive(A_pad, B_pad, C_pad, s);

    for (int i = 0; i < a_n; ++i)
        memcpy(C + i * c_n, C_pad + i * s, c_n * sizeof(double));

    liberar_matriz(A_pad);
    liberar_matriz(B_pad);
    liberar_matriz(C_pad);
}

int comparar(double* A, double* B, int n, double tol) {
    for (int i = 0; i < n * n; ++i)
        if (fabs(A[i] - B[i]) > tol)
            return 0;
    return 1;
}

void medir_rendimiento(int n) {
    printf("\nTamaño: %d x %d\n", n, n);
    double* A = crear_matriz(n);
    double* B = crear_matriz(n);
    double* C_naive = crear_matriz(n);
    double* C_strassen = crear_matriz(n);

    generar_aleatoria(A, n);
    generar_aleatoria(B, n);

    struct timespec start, end;
    size_t mem_before, mem_after;

    mem_before = getCurrentRSS();
    clock_gettime(CLOCK_MONOTONIC, &start);
    naive_multiply_avx(A, B, C_naive, n);
    clock_gettime(CLOCK_MONOTONIC, &end);
    mem_after = getCurrentRSS();
    printf("Naive:    %.2f ms, Mem: %zu KB\n", diff_ms(start, end), mem_after - mem_before);

    mem_before = getCurrentRSS();
    clock_gettime(CLOCK_MONOTONIC, &start);
    strassen(A, n, B, n, C_strassen, n);
    clock_gettime(CLOCK_MONOTONIC, &end);
    mem_after = getCurrentRSS();
    printf("Strassen: %.2f ms, Mem: %zu KB\n", diff_ms(start, end), mem_after - mem_before);

    if (!comparar(C_naive, C_strassen, n, 1e-5)) {
        printf("ERROR: Resultados no coinciden!\n");
        if (n == 128) {
            printf("Primeros valores Naive:\n");
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j)
                    printf("%8.4f ", C_naive[i * n + j]);
                printf("\n");
            }
            printf("Primeros valores Strassen:\n");
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j)
                    printf("%8.4f ", C_strassen[i * n + j]);
                printf("\n");
            }
        }
    }

    liberar_matriz(A);
    liberar_matriz(B);
    liberar_matriz(C_naive);
    liberar_matriz(C_strassen);
}

int main() {
    srand(time(NULL));
    int tamaños[] = {128, 256, 512, 1024};
    int n_tam = sizeof(tamaños) / sizeof(tamaños[0]);

    for (int i = 0; i < n_tam; i++) {
        medir_rendimiento(tamaños[i]);
    }
    return 0;
}
