
# CMake File
cmake_minimum_required(VERSION 3.0)
project(Custom_Iterator VERSION 0.1)

# set cpp standard
set(CMAKE_CXX_STANDARD 17)

# set projeczt wide include directories
include_directories(include)

# gather cpp files
set(CPP_FILES main.cpp)

# enable testing
enable_testing()

# build the executable
add_executable(main ${CPP_FILES})

# add the main executable as test
add_test(run main)