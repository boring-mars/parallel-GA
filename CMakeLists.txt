cmake_minimum_required(VERSION 3.29)
project(parallel_ga)

set(CMAKE_CXX_STANDARD 20)

add_executable(parallel_ga main.cpp
        Chromosome.h
        Chromosome.cpp)
