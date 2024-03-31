#include <mpi.h>
#include <unistd.h>
#include <cstdio>
#include <iomanip>

#include "communicationRingV2.hpp"
#include "src/utility/auxiliaryFunctions.hpp"

void CommunicationRingV2::run(int iter){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   
    int count = 1;

    if (rank == 0) printRow(std::vector<const char*>{"rank", "dest", "status", "source", "status"});
    sleep(1);
    MPI_Barrier(MPI_COMM_WORLD);

    for (int i=0; i < iter; i++){
    
        MPI_Request requests[2];
        MPI_Status status[2];   

        int dest = (rank+1) % world_size;
        int source = (rank + world_size - 1) % world_size;
        int rank_ = rank;
        int count = 0;
        int result;
        

        if(rank==0){
            usleep(500000);
            MPI_Issend(&count, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &requests[0]);
            MPI_Wait(&requests[0], &status[0]);

            usleep(500000);
            MPI_Irecv(&result, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &requests[1]);
            MPI_Wait(&requests[1], &status[1]);
        }else{
            usleep(500000);
            MPI_Irecv(&result, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &requests[0]);
            MPI_Wait(&requests[0], &status[0]);

            usleep(500000);
            MPI_Issend(&count, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &requests[1]);
            MPI_Wait(&requests[1], &status[1]);
        }
        
        count = result+count;
        char buffer[100];
        printRow(std::vector<int>{rank, dest, status[0].MPI_ERROR, source, status[0].MPI_ERROR});
        
        usleep(500000);
        MPI_Barrier(MPI_COMM_WORLD);
    }
}
