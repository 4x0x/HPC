
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 4

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int rows_per_proc = MATRIX_SIZE / world_size;

    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int vector[MATRIX_SIZE];
    int result[MATRIX_SIZE];

    int local_matrix[rows_per_proc][MATRIX_SIZE];
    int local_result[rows_per_proc];

    if (world_rank == 0) {
        // Initialize matrix and vector
        printf("Matrix:\n");
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                matrix[i][j] = i + j;
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

        printf("Vector:\n");
        for (int i = 0; i < MATRIX_SIZE; i++) {
            vector[i] = i;
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    // Scatter the matrix rows
    MPI_Scatter(matrix, rows_per_proc * MATRIX_SIZE, MPI_INT,
                local_matrix, rows_per_proc * MATRIX_SIZE, MPI_INT,
                0, MPI_COMM_WORLD);

    // Broadcast the vector to all processes
    MPI_Bcast(vector, MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Local computation
    for (int i = 0; i < rows_per_proc; i++) {
        local_result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            local_result[i] += local_matrix[i][j] * vector[j];
        }
    }

    // Gather the results
    MPI_Gather(local_result, rows_per_proc, MPI_INT,
               result, rows_per_proc, MPI_INT,
               0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Result of Matrix-Vector Multiplication:\n");
        for (int i = 0; i < MATRIX_SIZE; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
