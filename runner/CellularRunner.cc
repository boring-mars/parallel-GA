#include <random>
#include <iostream>
#include "CellularRunner.h"

CellularRunner::CellularRunner() {
    // Init the size of the cellular grid
    build_cellular(population_size);
}

void CellularRunner::build_cellular(int population_size) {
    // Find the size of the cellular grid which is as close to a square as possible
    cellular_row_size = static_cast<int>(std::sqrt(population_size));
    while (population_size % cellular_row_size != 0) {
        cellular_row_size--;
    }
    cellular_col_size = population_size / cellular_row_size;
}

Chromosome CellularRunner::pick_parent_from_neighbors(const Chromosome population[], int row, int col) const {
    // Compute the total fitness of the 3x3 neighborhood
    int total = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int neighbor_row = (row + i + cellular_row_size) % cellular_row_size;
            int neighbor_col = (col + j + cellular_col_size) % cellular_col_size;
            total += population[neighbor_row * cellular_col_size + neighbor_col].get_fitness();
        }
    }

    // Randomly select a point in the fitness distribution
    thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, total);
    int pick_point = distribution(generator);

    // Select a parent from the 3x3 neighborhood using roulette selection
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
