#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000 // Tamanho da matriz
#define BLOCK_SIZE 32 // Tamanho do bloco para blocagem

void inicializar_matriz(int **matriz, int n, int aleatorio) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = aleatorio ? (rand() % 31 + 10) : (i + j);
        }
    }
}

void multiplicar_matrizes(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiplicar_matrizes_blocagem(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i += BLOCK_SIZE) {
        for (int j = 0; j < n; j += BLOCK_SIZE) {
            for (int k = 0; k < n; k += BLOCK_SIZE) {
                for (int ii = i; ii < i + BLOCK_SIZE && ii < n; ii++) {
                    for (int jj = j; jj < j + BLOCK_SIZE && jj < n; jj++) {
                        for (int kk = k; kk < k + BLOCK_SIZE && kk < n; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

void contar_pares(int **matriz, int n, int ordem) {
    int contagem = 0;
    if (ordem == 0) { // Ordem por linha
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matriz[i][j] % 2 == 0) contagem++;
            }
        }
    } else { // Ordem por coluna
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                if (matriz[i][j] % 2 == 0) contagem++;
            }
        }
    }
    printf("Número de elementos pares: %d\n", contagem);
}

int main() {
    srand(time(NULL));
    int **A, **B, **C;

    // Alocação dinâmica das matrizes
    A = (int **)malloc(N * sizeof(int *));
    B = (int **)malloc(N * sizeof(int *));
    C = (int **)malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    inicializar_matriz(A, N, 0);  // Inicialização fixa para testes
    inicializar_matriz(B, N, 0);  // Inicialização fixa para testes

    clock_t inicio = clock();
    multiplicar_matrizes(A, B, C, N);
    clock_t fim = clock();

    printf("Tempo para multiplicação (linha): %.6f segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    multiplicar_matrizes_blocagem(A, B, C, N);
    fim = clock();

    printf("Tempo para multiplicação (blocagem): %.6f segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    contar_pares(A, N, 0);
    contar_pares(A, N, 1);

    // Liberação da memória
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
