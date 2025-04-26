
#include <mpi.h>
#include <stdio.h>
#include <unistd.h> // For sleep

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double start = MPI_Wtime();

    // Simulate work
    sleep(1 + world_rank); // Different sleep time for each process

    double end = MPI_Wtime();
    printf("Process %d finished work in %f seconds\n", world_rank, end - start);

    MPI_Finalize();
    return 0;
}
