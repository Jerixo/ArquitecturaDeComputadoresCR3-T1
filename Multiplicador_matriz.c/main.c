#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/matrix_utils.h"
#include "include/naive_multiply.h"
#include "include/strassen_multiply.h"
#include "include/benchmark.h"

#define REPETICIONES 3
#define EPSILON 0.0001

void guardar_csv(const char* algoritmo, int n, double tiempo_ms, double memoria_mb) {
    FILE* archivo = fopen("resultados/resultados.csv", "a");
    if (archivo == NULL) {
        printf("Error al guardar archivo CSV.\n");
        return;
    }
    fprintf(archivo, "%s,%d,%.3f,%.2f\n", algoritmo, n, tiempo_ms, memoria_mb);
    fclose(archivo);
}

void ejecutar_y_guardar(const char* algoritmo, int n, int usar_strassen) {
    double tiempo_total = 0.0;

    for (int r = 0; r < REPETICIONES; r++) {
        double** A = create_matrix(n);
        double** B = create_matrix(n);
        double** C = create_matrix(n);

        fill_matrix_random(A, n);
        fill_matrix_random(B, n);

        clock_t inicio = clock();

        if (usar_strassen) {
            strassen_multiply(A, B, C, n);
        } else {
            naive_multiply(A, B, C, n);
        }

        clock_t fin = clock();
        double t_ms = elapsed_time(inicio, fin) * 1000.0; 
        printf("[%s] Repetición %d (n=%d): %.3f ms\n", algoritmo, r + 1, n, t_ms);
        tiempo_total += t_ms;

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    double promedio = tiempo_total / REPETICIONES;
    double memoria_mb = 3.0 * n * n * sizeof(double) / (1024.0 * 1024.0);

    printf(">> [%s] Tiempo promedio: %.3f ms | Memoria estimada: %.2f MB\n\n", algoritmo, promedio, memoria_mb);
    guardar_csv(algoritmo, n, promedio, memoria_mb);
}

int main() {
    FILE* archivo = fopen("resultados/resultados.csv", "w");
    if (archivo != NULL) {
        fprintf(archivo, "Algoritmo,Tamaño,Tiempo(ms),Memoria(MB)\n");
        fclose(archivo);
    }

    int tamanos[] = {128, 256, 512, 1024};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    for (int i = 0; i < num_tamanos; i++) {
        int n = tamanos[i];
        ejecutar_y_guardar("Naive", n, 0);
        ejecutar_y_guardar("Strassen", n, 1);
    }

    printf("Pruebas finalizadas. Resultados en 'resultados/resultados.csv'");
    return 0;
}
