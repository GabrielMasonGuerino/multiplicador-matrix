#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000  // Tamanho da matriz

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

int contar_pares(int **matriz, int n, int ordem) {
    int contagem = 0;
    if (ordem == 0) {  // Percorrendo por linhas
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (matriz[i][j] % 2 == 0)
                    contagem++;
    } else {  // Percorrendo por colunas
        for (int j = 0; j < n; j++)
            for (int i = 0; i < n; i++)
                if (matriz[i][j] % 2 == 0)
                    contagem++;
    }
    return contagem;
}

int main() {
    srand(time(NULL));

    // Alocação dinâmica das matrizes
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    inicializar_matriz(A, N, 0);
    inicializar_matriz(B, N, 0);

    clock_t inicio = clock();
    multiplicar_matrizes(A, B, C, N);
    clock_t fim = clock();
    
    printf("Tempo de multiplicação: %.4f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Quantidade de pares (linha): %d\n", contar_pares(C, N, 0));
    printf("Quantidade de pares (coluna): %d\n", contar_pares(C, N, 1));

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
