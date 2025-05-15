import random
import time
import tracemalloc
import csv
from typing import List, Tuple
import matplotlib.pyplot as plt

# --- Definición de tipos ---
Matrix = List[List[float]]

# --- Generadores y utilidades ---
def generate_random_matrix(rows: int, cols: int) -> Matrix:
    """Genera una matriz de tamaño rows x cols con valores aleatorios en [0,1)."""
    return [[random.random() for _ in range(cols)] for _ in range(rows)]


def compare_matrices(A: Matrix, B: Matrix, tol: float = 1e-6) -> bool:
    """Compara dos matrices elemento a elemento con tolerancia."""
    if len(A) != len(B) or len(A[0]) != len(B[0]):
        return False
    return all(abs(A[i][j] - B[i][j]) < tol
               for i in range(len(A))
               for j in range(len(A[0])))

# --- Implementaciones de multiplicación ---

def naive_multiply(A: Matrix, B: Matrix) -> Matrix:
    m, p = len(A), len(A[0])
    p2, n = len(B), len(B[0])
    assert p == p2, "Dimensiones incompatibles"
    C = [[0.0] * n for _ in range(m)]
    for i in range(m):
        for k in range(p):
            aik = A[i][k]
            for j in range(n):
                C[i][j] += aik * B[k][j]
    return C


def blocked_multiply(A: Matrix, B: Matrix, b: int) -> Matrix:
    m, p = len(A), len(A[0])
    p2, n = len(B), len(B[0])
    assert p == p2, "Dimensiones incompatibles"
    C = [[0.0] * n for _ in range(m)]
    for ii in range(0, m, b):
        for kk in range(0, p, b):
            for jj in range(0, n, b):
                for i in range(ii, min(ii + b, m)):
                    for k in range(kk, min(kk + b, p)):
                        aik = A[i][k]
                        for j in range(jj, min(jj + b, n)):
                            C[i][j] += aik * B[k][j]
    return C


def add_matrix(A: Matrix, B: Matrix) -> Matrix:
    m, n = len(A), len(A[0])
    return [[A[i][j] + B[i][j] for j in range(n)] for i in range(m)]


def sub_matrix(A: Matrix, B: Matrix) -> Matrix:
    m, n = len(A), len(A[0])
    return [[A[i][j] - B[i][j] for j in range(n)] for i in range(m)]


def strassen_multiply(A: Matrix, B: Matrix) -> Matrix:
    def next_power_of_two(x):
        p = 1
        while p < x:
            p <<= 1
        return p

    def pad(M: Matrix, size: int) -> Matrix:
        m, n = len(M), len(M[0])
        P = [[0.0] * size for _ in range(size)]
        for i in range(m):
            for j in range(n):
                P[i][j] = M[i][j]
        return P

    def unpad(M: Matrix, rows: int, cols: int) -> Matrix:
        return [row[:cols] for row in M[:rows]]

    n_max = max(len(A), len(A[0]), len(B), len(B[0]))
    s = next_power_of_two(n_max)
    A_pad = pad(A, s)
    B_pad = pad(B, s)

    def strassen(X: Matrix, Y: Matrix, size: int) -> Matrix:
        if size == 1:
            return [[X[0][0] * Y[0][0]]]
        mid = size // 2
        # Partición en cuadrantes
        A11 = [row[:mid] for row in X[:mid]]
        A12 = [row[mid:] for row in X[:mid]]
        A21 = [row[:mid] for row in X[mid:]]
        A22 = [row[mid:] for row in X[mid:]]
        B11 = [row[:mid] for row in Y[:mid]]
        B12 = [row[mid:] for row in Y[:mid]]
        B21 = [row[:mid] for row in Y[mid:]]
        B22 = [row[mid:] for row in Y[mid:]]

        # 7 productos de Strassen
        M1 = strassen(add_matrix(A11, A22), add_matrix(B11, B22), mid)
        M2 = strassen(add_matrix(A21, A22), B11, mid)
        M3 = strassen(A11, sub_matrix(B12, B22), mid)
        M4 = strassen(A22, sub_matrix(B21, B11), mid)
        M5 = strassen(add_matrix(A11, A12), B22, mid)
        M6 = strassen(sub_matrix(A21, A11), add_matrix(B11, B12), mid)
        M7 = strassen(sub_matrix(A12, A22), add_matrix(B21, B22), mid)

        # Combina resultados
        C11 = add_matrix(sub_matrix(add_matrix(M1, M4), M5), M7)
        C12 = add_matrix(M3, M5)
        C21 = add_matrix(M2, M4)
        C22 = add_matrix(sub_matrix(add_matrix(M1, M3), M2), M6)

        # Ensamblaje
        C = [[0.0] * size for _ in range(size)]
        for i in range(mid):
            C[i][:mid] = C11[i]
            C[i][mid:] = C12[i]
        for i in range(mid):
            C[mid + i][:mid] = C21[i]
            C[mid + i][mid:] = C22[i]
        return C

    C_full = strassen(A_pad, B_pad, s)
    return unpad(C_full, len(A), len(B[0]))

# --- Benchmarking ---

def benchmark(sizes: List[int], repeats: int = 3, block_size: int = 64) -> List[Tuple]:
    """
    Ejecuta mediciones de tiempo y memoria para cada tamaño y algoritmo.
    Devuelve lista de tuplas: (n, algoritmo, tiempo_ms, mem_kb).
    """
    results = []
    for n in sizes:
        # Genera matrices cuadradas de tamaño nxn
        A = generate_random_matrix(n, n)
        B = generate_random_matrix(n, n)
        # Copia de validación con naive
        C_ref = naive_multiply(A, B)

        for name, func in [
            ("naive", naive_multiply),
            ("blocked", lambda X, Y: blocked_multiply(X, Y, block_size)),
            ("strassen", strassen_multiply)
        ]:
            # Medición de tiempo
            t0 = time.perf_counter()
            for _ in range(repeats):
                C = func(A, B)
            t1 = time.perf_counter()
            time_ms = (t1 - t0) / repeats * 1000

            # Verificación
            assert compare_matrices(C, C_ref), f"Error en {name} para n={n}"

            # Medición de memoria pico
            tracemalloc.start()
            _ = func(A, B)
            current, peak = tracemalloc.get_traced_memory()
            tracemalloc.stop()
            mem_kb = peak / 1024

            results.append((n, name, time_ms, mem_kb))
            print(f"n={n}, alg={name}, time={time_ms:.2f}ms, mem={mem_kb:.1f}KB")
    return results

# --- Generación de CSV y gráficas ---

def save_results_csv(results: List[Tuple], filename: str = "benchmark_results.csv"):
    with open(filename, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["n", "algorithm", "time_ms", "mem_kb"])
        writer.writerows(results)
    print(f"Resultados guardados en {filename}")


def plot_results(results: List[Tuple]):
    import matplotlib.pyplot as plt
    # Organiza por algoritmo
    algos = sorted(set(r[1] for r in results))
    for name in algos:
        xs = [r[0] for r in results if r[1] == name]
        ys = [r[2] for r in results if r[1] == name]
        plt.plot(xs, ys, label=name)
    plt.xlabel("Tamaño n")
    plt.ylabel("Tiempo medio (ms)")
    plt.title("Comparativa de tiempos de multiplicación de matrices")
    plt.legend()
    plt.grid(True)
    plt.show()

# --- Ejecución principal ---
if __name__ == "__main__":
    sizes = [128, 256, 512, 1024]
    results = benchmark(sizes, repeats=3, block_size=64)
    save_results_csv(results)
    plot_results(results)
