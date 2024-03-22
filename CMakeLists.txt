cmake_minimum_required(VERSION 3.10)
project(NDMC)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add the executable
add_executable(NDMC ${SOURCES})

# Set the path to the Score-P MPI C++ compiler
set(SCOREP_MPI_CXX_COMPILER "/opt/scorep/bin/scorep-mpicxx")

# Check if Score-P MPI C++ compiler is installed
find_program(SCOREP_MPI_CXX_FOUND NAMES scorep mpicxx PATHS "/opt/scorep/bin")

if (NOT SCOREP_MPI_CXX_FOUND)
    message(FATAL_ERROR "Score-P MPI C++ compiler not found in /opt/scorep/bin")
endif()

# Set the C++ compiler to Score-P MPI C++ compiler
set(CMAKE_CXX_COMPILER "${SCOREP_MPI_CXX_COMPILER}")