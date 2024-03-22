#include <mpi.h>
#include <iostream>
#include <unistd.h>

#include "miniRaceCondition.hpp"

void MiniRaceCondition::run(int iter){
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int result, data;
    MPI_Request requests[size-1];

     for (int i=0; i < iter; i++){
        if(rank == 0) {
            for(int i = 0; i < size-1; i++) {
                usleep(5000);
                MPI_Irecv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &requests[i]);
            }
            MPI_Waitall(size-1, requests, MPI_STATUS_IGNORE);
            result=data;

        } else {
            data = rank; 
            MPI_Isend(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[0]);
            MPI_Wait(&requests[0], MPI_STATUS_IGNORE);
        }

        usleep(15000);
        MPI_Barrier(MPI_COMM_WORLD);
        if(rank == 0) {
        }
     }
}