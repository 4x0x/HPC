#include <stdio.h>
#include <omp.h>

#define N 256  // Matrix size (N x N)

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices A and B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0; // Clear C
        }
    }

    double start = omp_get_wtime();  // Start timing

    // Offload matrix multiplication to GPU
#pragma omp target map(to: A, B) map(from: C)
    {
#pragma omp parallel for collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int sum = 0;
                for (int k = 0; k < N; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }
    }

    double end = omp_get_wtime();  // End timing

    printf("C[0][0] = %d, C[N-1][N-1] = %d\n", C[0][0], C[N-1][N-1]);
    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
