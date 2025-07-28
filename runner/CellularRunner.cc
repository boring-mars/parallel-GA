#include <random>
#include <iostream>
#include <algorithm>
#include "CellularRunner.h"

Chromosome CellularRunner::pick_parent_from_neighbors(const Chromosome population[], int row, int col) {
    // Fill the neighbors array with the neighboring chromosomes
    Chromosome neighbors[3][3];
    double possibilities[3][3];
    double total = 0.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int neighbor_row = (row + i - 1 + cellular_row_size) % cellular_row_size;
            int neighbor_col = (col + j - 1 + cellular_col_size) % cellular_col_size;
            neighbors[i][j] = population[neighbor_row * cellular_col_size + neighbor_col];
            possibilities[i][j] = neighbors[i][j].get_fitness() / double(max_fitness);
            total += possibilities[i][j];
        }
    }

    static std::mt19937 generator = std::mt19937(std::random_device{}());
    std::uniform_real_distribution<> distribution(0, total);
    double pick_point = distribution(generator);

    double accumulator = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            accumulator += possibilities[i][j];
            if (accumulator >= pick_point) {
                return neighbors[i][j];
            }
        }
    }

    throw std::runtime_error("No parent found, this should not happen.");
}
