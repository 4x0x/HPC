
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int value;
    if (world_rank == 0) {
        value = 55; // Value to broadcast
    }

    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received value %d after broadcast\n", world_rank, value);

    MPI_Finalize();
    return 0;
}
