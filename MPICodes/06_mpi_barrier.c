
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    printf("Process %d reached before barrier\n", world_rank);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("Process %d passed the barrier\n", world_rank);

    MPI_Finalize();
    return 0;
}
