
#include <mpi.h>
#include <stdio.h>
#include <stddef.h> // For offsetof

typedef struct {
    int id;
    float value;
} Data;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    Data my_data;
    MPI_Datatype MPI_Data_Type;

    int lengths[2] = {1, 1};
    MPI_Aint displacements[2];
    MPI_Datatype types[2] = {MPI_INT, MPI_FLOAT};

    displacements[0] = offsetof(Data, id);
    displacements[1] = offsetof(Data, value);

    MPI_Type_create_struct(2, lengths, displacements, types, &MPI_Data_Type);
    MPI_Type_commit(&MPI_Data_Type);

    if (world_rank == 0) {
        my_data.id = 101;
        my_data.value = 3.14;
        MPI_Send(&my_data, 1, MPI_Data_Type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent struct {id: %d, value: %.2f}\n", my_data.id, my_data.value);
    } else if (world_rank == 1) {
        MPI_Recv(&my_data, 1, MPI_Data_Type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received struct {id: %d, value: %.2f}\n", my_data.id, my_data.value);
    }

    MPI_Type_free(&MPI_Data_Type);
    MPI_Finalize();
    return 0;
}
