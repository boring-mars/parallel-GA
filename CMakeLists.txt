cmake_minimum_required(VERSION 3.29)
project(parallel_ga)

set(CMAKE_CXX_STANDARD 20)

add_executable(parallel_ga main.cc
        model/Chromosome.h
        model/Chromosome.cc
        runner/Runner.h
        runner/Runner.cc
        runner/SerialRunner.h
        runner/SerialRunner.cc
        runner/OpenMPRunner.h
        runner/OpenMPRunner.cc
        RunningConfig.h)

find_package(OpenMP REQUIRED)
target_link_libraries(parallel_ga PRIVATE OpenMP::OpenMP_CXX)