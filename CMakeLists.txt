cmake_minimum_required(VERSION 3.29)
project(parallel_ga)

set(CMAKE_CXX_STANDARD 20)

add_executable(parallel_ga main.cpp
        Chromosome.h
        Chromosome.cpp
        runner/Runner.h
        runner/Runner.cpp
        runner/SerialRunner.h
        runner/SerialRunner.cpp
        runner/OpenMPRunner.h
        runner/OpenMPRunner.cpp)

find_package(OpenMP REQUIRED)
target_link_libraries(parallel_ga PRIVATE OpenMP::OpenMP_CXX)