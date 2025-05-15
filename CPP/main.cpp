#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>

using Matrix = std::vector<std::vector<double>>;

// --- Función para obtener memoria residente actual (VmRSS) en KB ---
size_t getCurrentRSS() {
    std::ifstream stat_stream("/proc/self/status", std::ios_base::in);
    std::string line;
    while (std::getline(stat_stream, line)) {
        if (line.compare(0, 6, "VmRSS:") == 0) {
            size_t pos = line.find_first_of("0123456789");
            if (pos != std::string::npos) {
                size_t end_pos = line.find(" kB", pos);
                if (end_pos != std::string::npos) {
                    std::string number = line.substr(pos, end_pos - pos);
                    return std::stoul(number); // en KB
                }
            }
        }
    }
    return 0;
}

// --- Resto del código (generación, multiplicación, etc.) ---

Matrix generate_random_matrix(int rows, int cols) {
    Matrix M(rows, std::vector<double>(cols));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            M[i][j] = dist(gen);
    return M;
}

bool compare_matrices(const Matrix& A, const Matrix& B, double tol = 1e-6) {
    if (A.size() != B.size() || A[0].size() != B[0].size())
        return false;
    for (size_t i = 0; i < A.size(); ++i)
        for (size_t j = 0; j < A[0].size(); ++j)
            if (std::abs(A[i][j] - B[i][j]) >= tol)
                return false;
    return true;
}

Matrix naive_multiply(const Matrix& A, const Matrix& B) {
    int m = (int)A.size();
    int p = (int)A[0].size();
    int p2 = (int)B.size();
    int n = (int)B[0].size();
    assert(p == p2 && "Dimensiones incompatibles");
    Matrix C(m, std::vector<double>(n, 0.0));
    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < p; ++k) {
            double aik = A[i][k];
            for (int j = 0; j < n; ++j) {
                C[i][j] += aik * B[k][j];
            }
        }
    }
    return C;
}

Matrix blocked_multiply(const Matrix& A, const Matrix& B, int b) {
    int m = (int)A.size();
    int p = (int)A[0].size();
    int p2 = (int)B.size();
    int n = (int)B[0].size();
    assert(p == p2 && "Dimensiones incompatibles");
    Matrix C(m, std::vector<double>(n, 0.0));
    for (int ii = 0; ii < m; ii += b) {
        for (int kk = 0; kk < p; kk += b) {
            for (int jj = 0; jj < n; jj += b) {
                for (int i = ii; i < std::min(ii + b, m); ++i) {
                    for (int k = kk; k < std::min(kk + b, p); ++k) {
                        double aik = A[i][k];
                        for (int j = jj; j < std::min(jj + b, n); ++j) {
                            C[i][j] += aik * B[k][j];
                        }
                    }
                }
            }
        }
    }
    return C;
}

Matrix add_matrix(const Matrix& A, const Matrix& B) {
    int m = (int)A.size();
    int n = (int)A[0].size();
    Matrix C(m, std::vector<double>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix sub_matrix(const Matrix& A, const Matrix& B) {
    int m = (int)A.size();
    int n = (int)A[0].size();
    Matrix C(m, std::vector<double>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix pad(const Matrix& M, int size) {
    int m = (int)M.size();
    int n = (int)M[0].size();
    Matrix P(size, std::vector<double>(size, 0.0));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            P[i][j] = M[i][j];
    return P;
}

Matrix unpad(const Matrix& M, int rows, int cols) {
    Matrix R(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            R[i][j] = M[i][j];
    return R;
}

int next_power_of_two(int x) {
    int p = 1;
    while (p < x)
        p <<= 1;
    return p;
}

Matrix strassen_recursive(const Matrix& X, const Matrix& Y, int size) {
    if (size == 1) {
        return Matrix{{X[0][0] * Y[0][0]}};
    }
    int mid = size / 2;

    Matrix A11(mid, std::vector<double>(mid));
    Matrix A12(mid, std::vector<double>(mid));
    Matrix A21(mid, std::vector<double>(mid));
    Matrix A22(mid, std::vector<double>(mid));
    Matrix B11(mid, std::vector<double>(mid));
    Matrix B12(mid, std::vector<double>(mid));
    Matrix B21(mid, std::vector<double>(mid));
    Matrix B22(mid, std::vector<double>(mid));

    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            A11[i][j] = X[i][j];
            A12[i][j] = X[i][j + mid];
            A21[i][j] = X[i + mid][j];
            A22[i][j] = X[i + mid][j + mid];

            B11[i][j] = Y[i][j];
            B12[i][j] = Y[i][j + mid];
            B21[i][j] = Y[i + mid][j];
            B22[i][j] = Y[i + mid][j + mid];
        }
    }

    Matrix M1 = strassen_recursive(add_matrix(A11, A22), add_matrix(B11, B22), mid);
    Matrix M2 = strassen_recursive(add_matrix(A21, A22), B11, mid);
    Matrix M3 = strassen_recursive(A11, sub_matrix(B12, B22), mid);
    Matrix M4 = strassen_recursive(A22, sub_matrix(B21, B11), mid);
    Matrix M5 = strassen_recursive(add_matrix(A11, A12), B22, mid);
    Matrix M6 = strassen_recursive(sub_matrix(A21, A11), add_matrix(B11, B12), mid);
    Matrix M7 = strassen_recursive(sub_matrix(A12, A22), add_matrix(B21, B22), mid);

    Matrix C11 = add_matrix(sub_matrix(add_matrix(M1, M4), M5), M7);
    Matrix C12 = add_matrix(M3, M5);
    Matrix C21 = add_matrix(M2, M4);
    Matrix C22 = add_matrix(sub_matrix(add_matrix(M1, M3), M2), M6);

    Matrix C(size, std::vector<double>(size));

    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

    return C;
}

Matrix strassen_multiply(const Matrix& A, const Matrix& B) {
    int n_max = std::max({(int)A.size(), (int)A[0].size(), (int)B.size(), (int)B[0].size()});
    int s = next_power_of_two(n_max);

    Matrix A_pad = pad(A, s);
    Matrix B_pad = pad(B, s);

    Matrix C_pad = strassen_recursive(A_pad, B_pad, s);

    return unpad(C_pad, (int)A.size(), (int)B[0].size());
}

// --- Benchmarking ---

struct BenchmarkResult {
    int n;
    std::string algorithm;
    double time_ms;
    double mem_kb;
};

std::vector<BenchmarkResult> benchmark(const std::vector<int>& sizes, int repeats = 3, int block_size = 64) {
    std::vector<BenchmarkResult> results;
    for (int n : sizes) {
        Matrix A = generate_random_matrix(n, n);
        Matrix B = generate_random_matrix(n, n);
        Matrix C_ref = naive_multiply(A, B);

        // Naive
        {
            size_t mem_before = getCurrentRSS();
            auto start = std::chrono::high_resolution_clock::now();
            Matrix C;
            for (int r = 0; r < repeats; ++r)
                C = naive_multiply(A, B);
            auto end = std::chrono::high_resolution_clock::now();
            size_t mem_after = getCurrentRSS();

            double time_ms = std::chrono::duration<double, std::milli>(end - start).count() / repeats;
            size_t mem_used = (mem_after > mem_before) ? (mem_after - mem_before) : 0;

            assert(compare_matrices(C, C_ref) && "Error en naive_multiply");
            results.push_back({n, "naive", time_ms, (double)mem_used});
            std::cout << "n=" << n << ", alg=naive, time=" << time_ms << " ms, mem=" << mem_used << " KB\n";
        }

        // Blocked
        {
            size_t mem_before = getCurrentRSS();
            auto start = std::chrono::high_resolution_clock::now();
            Matrix C;
            for (int r = 0; r < repeats; ++r)
                C = blocked_multiply(A, B, block_size);
            auto end = std::chrono::high_resolution_clock::now();
            size_t mem_after = getCurrentRSS();

            double time_ms = std::chrono::duration<double, std::milli>(end - start).count() / repeats;
            size_t mem_used = (mem_after > mem_before) ? (mem_after - mem_before) : 0;

            assert(compare_matrices(C, C_ref) && "Error en blocked_multiply");
            results.push_back({n, "blocked", time_ms, (double)mem_used});
            std::cout << "n=" << n << ", alg=blocked, time=" << time_ms << " ms, mem=" << mem_used << " KB\n";
        }

        // Strassen
        {
            size_t mem_before = getCurrentRSS();
            auto start = std::chrono::high_resolution_clock::now();
            Matrix C;
            for (int r = 0; r < repeats; ++r)
                C = strassen_multiply(A, B);
            auto end = std::chrono::high_resolution_clock::now();
            size_t mem_after = getCurrentRSS();

            double time_ms = std::chrono::duration<double, std::milli>(end - start).count() / repeats;
            size_t mem_used = (mem_after > mem_before) ? (mem_after - mem_before) : 0;

            assert(compare_matrices(C, C_ref) && "Error en strassen_multiply");
            results.push_back({n, "strassen", time_ms, (double)mem_used});
            std::cout << "n=" << n << ", alg=strassen, time=" << time_ms << " ms, mem=" << mem_used << " KB\n";
        }
    }
    return results;
}

void save_results_csv(const std::vector<BenchmarkResult>& results, const std::string& filename = "benchmark_results.csv") {
    std::ofstream f(filename);
    f << "n,algorithm,time_ms,mem_kb\n";
    for (auto& r : results) {
        f << r.n << "," << r.algorithm << "," << r.time_ms << "," << r.mem_kb << "\n";
    }
    std::cout << "Resultados guardados en " << filename << std::endl;
}

int main() {
    std::vector<int> sizes = {128, 256, 512, 1024};
    auto results = benchmark(sizes, 3, 64);
    save_results_csv(results);
    return 0;
}
