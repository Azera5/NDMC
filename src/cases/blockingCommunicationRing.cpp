#include <mpi.h>
#include <unistd.h>
#include <cstdio>
#include <iomanip>

#include "blockingCommunicationRing.hpp"
#include "src/utility/auxiliaryFunctions.hpp"

void BlockingCommunicationRing::run(int iter){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   
    int count = 1;

    if (rank == 0) printRow(std::vector<const char*>{"rank", "dest", "source"});
    sleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
      
    for (int i=0; i < iter; i++){
        int dest = (rank+1) % world_size;
        int source = (rank + world_size - 1) % world_size;
        int rank_ = rank;
        int count = 0;
        int result;

        char buffer[100];
        printRow(std::vector<int>{rank, dest, source});

        if(rank == 0)
        {
            usleep(500000);
            MPI_Send(&count, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            
            usleep(500000);
            MPI_Recv(&result, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else
        {
            usleep(500000);
            MPI_Recv(&result, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            usleep(500000);
            MPI_Send(&count, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);

        }
        
        MPI_Barrier(MPI_COMM_WORLD);
        count = result+count;
        printRow(std::vector<int>{rank, dest, source});
    }
}
