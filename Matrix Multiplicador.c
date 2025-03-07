#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

#define N 1000  // Definição do tamanho da matriz

// Função para inicializar as matrizes
void initializeMatrices(vector<vector<int>>& A, vector<vector<int>>& B) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i * j;
        }
    }
}

// Contagem de elementos pares (ordem por linha)
int countEvenRowOrder(const vector<vector<int>>& A) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] % 2 == 0)
                count++;
        }
    }
    return count;
}

// Contagem de elementos pares (ordem por coluna)
int countEvenColumnOrder(const vector<vector<int>>& A) {
    int count = 0;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (A[i][j] % 2 == 0)
                count++;
        }
    }
    return count;
}

// Multiplicação de matrizes (ordem por linha)
void multiplyMatricesRowOrder(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Multiplicação de matrizes (ordem por blocagem)
void multiplyMatricesBlocked(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int blockSize) {
    for (int i = 0; i < N; i += blockSize) {
        for (int j = 0; j < N; j += blockSize) {
            for (int k = 0; k < N; k += blockSize) {
                for (int ii = i; ii < min(i + blockSize, N); ii++) {
                    for (int jj = j; jj < min(j + blockSize, N); jj++) {
                        for (int kk = k; kk < min(k + blockSize, N); kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> A(N, vector<int>(N)), B(N, vector<int>(N)), C(N, vector<int>(N, 0));
    initializeMatrices(A, B);

    // Medindo tempo para contagem de elementos pares (ordem por linha)
    auto start = high_resolution_clock::now();
    int evenCountRow = countEvenRowOrder(A);
    auto stop = high_resolution_clock::now();
    cout << "Elementos pares (ordem linha): " << evenCountRow << " Tempo: " << duration<double>(stop - start).count() << " segs" << endl;

    // Medindo tempo para contagem de elementos pares (ordem por coluna)
    start = high_resolution_clock::now();
    int evenCountCol = countEvenColumnOrder(A);
    stop = high_resolution_clock::now();
    cout << "Elementos pares (ordem coluna): " << evenCountCol << " Tempo: " << duration<double>(stop - start).count() << " segs" << endl;

    // Medindo tempo para multiplicação de matrizes (ordem por linha)
    start = high_resolution_clock::now();
    multiplyMatricesRowOrder(A, B, C);
    stop = high_resolution_clock::now();
    cout << "Multiplicação (ordem linha): " << duration<double>(stop - start).count() << " segs" << endl;

    // Medindo tempo para multiplicação de matrizes (ordem por blocagem)
    int blockSize = 32;  // Definir um tamanho adequado para o cache
    C.assign(N, vector<int>(N, 0));  // Resetando matriz C
    start = high_resolution_clock::now();
    multiplyMatricesBlocked(A, B, C, blockSize);
    stop = high_resolution_clock::now();
    cout << "Multiplicação (blocos): " << duration<double>(stop - start).count() << " segs" << endl;

    return 0;
}
