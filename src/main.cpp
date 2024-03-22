#include <mpi.h>
#include <iostream>
#include <string>
#include "cases/communicationRing.hpp"
#include "cases/blockingCommunicationRing.hpp"
#include "cases/miniRaceCondition.hpp"

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    // Default program identifier
    int programId = 0;

    // Analyze command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-r" && i + 1 < argc) {
            programId = std::stoi(argv[++i]);
        } else if (arg == "-p") {
            std::cout  << "Programs:\n"
                << "  1    CommunicationRing - non-blocking\n"
                << "  2    CommunicationRing - blocking\n"
                << "  3    RaceCondition\n"            
                << std::endl;
            MPI_Finalize();
            return 0;
        } else if (arg == "-h") {
            std::cout  << "Options:\n"
                << "  -r    Specify the program ID to run\n"
                << "  -p    Show the program ID list\n"
                << "  -h    Show this help message\n"            
                << std::endl;
            MPI_Finalize();
            return 0;
        } else {
            std::cerr << "Unknown argument or missing value after '-r': " << arg << std::endl;
            MPI_Finalize();
            return 1;
        }
    }

    switch (programId) {
    case 1:
        CommunicationRing::run(1);
        break;
    case 2: 
        BlockingCommunicationRing::run(1);
        break;
    case 3:
        MiniRaceCondition::run(1);
        break;
    // Add more cases here for additional programs
    default:
        std::cout << "Usage: " << argv[0] << " -r <programId>\n"
            << "Options:\n"
            << "  -r    Specify the program ID to run\n"
            << "  -p    Show the program ID list\n"
            << "  -h    Show this help message\n"            
            << std::endl;
        break;
    }

    MPI_Finalize();
    return 0;
}
