
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_SIZE 8

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int *A = NULL;
    int *B = NULL;
    int *C = NULL;

    int chunk_size = VECTOR_SIZE / world_size;

    int local_A[chunk_size];
    int local_B[chunk_size];
    int local_C[chunk_size];

    if (world_rank == 0) {
        // Initialize vectors A and B
        A = (int*)malloc(VECTOR_SIZE * sizeof(int));
        B = (int*)malloc(VECTOR_SIZE * sizeof(int));
        C = (int*)malloc(VECTOR_SIZE * sizeof(int));

        for (int i = 0; i < VECTOR_SIZE; i++) {
            A[i] = i;
            B[i] = i * 2;
        }
    }

    // Scatter the vectors to all processes
    MPI_Scatter(A, chunk_size, MPI_INT, local_A, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, chunk_size, MPI_INT, local_B, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local addition
    for (int i = 0; i < chunk_size; i++) {
        local_C[i] = local_A[i] + local_B[i];
    }

    // Gather the results back
    MPI_Gather(local_C, chunk_size, MPI_INT, C, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Result Vector C = [");
        for (int i = 0; i < VECTOR_SIZE; i++) {
            printf("%d ", C[i]);
        }
        printf("]\n");
        free(A);
        free(B);
        free(C);
    }

    MPI_Finalize();
    return 0;
}
