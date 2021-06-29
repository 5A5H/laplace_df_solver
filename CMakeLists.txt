
# CMake File
cmake_minimum_required(VERSION 3.0)
project(Custom_Iterator VERSION 0.1)

# set cpp standard
set(CMAKE_CXX_STANDARD 17)

# setup parallel
find_package(MPI)

# set projeczt wide include directories
include_directories(include ${MPI_INCLUDE_PATH})

# gather cpp files
set(CPP_FILES main.cpp)

# enable testing
enable_testing()

# build the executable
add_executable(main ${CPP_FILES})
add_executable(main_mpi main_mpi.cpp)

# link executables to mpi
target_link_libraries(main_mpi ${MPI_CXX_LIBRARIES})

# add the main executable as test
add_test(run main)
