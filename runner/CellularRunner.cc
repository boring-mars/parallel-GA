#include <random>
#include <iostream>
#include "CellularRunner.h"

CellularRunner::CellularRunner()
        : cellular_row_size(RunningConfig::cellular_row_size),
          cellular_col_size(RunningConfig::cellular_col_size) {
    // TODO: Automatically calculate cellular_row_size and cellular_col_size based on population_size
}

Chromosome CellularRunner::pick_parent_from_neighbors(const Chromosome population[], int row, int col) const {
    int total = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int neighbor_row = (row + i + cellular_row_size) % cellular_row_size;
            int neighbor_col = (col + j + cellular_col_size) % cellular_col_size;
            total += population[neighbor_row * cellular_col_size + neighbor_col].get_fitness();
        }
    }

    thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, total);
    int pick_point = distribution(generator);

    int accumulator = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int neighbor_row = (row + i + cellular_row_size) % cellular_row_size;
            int neighbor_col = (col + j + cellular_col_size) % cellular_col_size;
            Chromosome neighbor = population[neighbor_row * cellular_col_size + neighbor_col];

            accumulator += neighbor.get_fitness();
            if (accumulator >= pick_point) {
                return neighbor;
            }
        }
    }

    throw std::runtime_error("No parent found, this should not happen.");
}
