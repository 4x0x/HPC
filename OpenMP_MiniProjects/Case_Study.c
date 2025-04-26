#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define MAX_VALUE 10

void generate_random_matrix(int **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % (MAX_VALUE + 1);
        }
    }
}

void sequential_matrix_multiply(int **A, int **B, int **C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void parallel_matrix_multiply(int **A, int **B, int **C) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double measure_execution_time(void (*function)(int **, int **, int **), int **A, int **B, int **C) {
    double start_time = omp_get_wtime();
    function(A, B, C);
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

int main() {
    srand(time(NULL));

    // Dynamically allocate matrices
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    // Generate random matrices
    generate_random_matrix(A);
    generate_random_matrix(B);

    // Measure execution time
    double sequential_time = measure_execution_time(sequential_matrix_multiply, A, B, C);
    printf("Sequential Execution Time: %lf seconds\n", sequential_time);

    double parallel_time = measure_execution_time(parallel_matrix_multiply, A, B, C);
    printf("Parallel Execution Time: %lf seconds\n", parallel_time);

    // Free memory
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
