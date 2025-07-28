#include <random>
#include <iostream>
#include "SerialCellularRunner.h"

Chromosome *SerialCellularRunner::generate_population(const Chromosome population[]) {
    auto *new_population = new Chromosome[population_size];

    for (int i = 0; i < population_size; ++i) {
        int row = i / cellular_col_size;
        int col = i % cellular_col_size;
        Chromosome x = pick_parent_from_neighbors(population, row, col);
        Chromosome y = pick_parent_from_neighbors(population, row, col);
        Chromosome child = x.cross_over(y);

        static std::mt19937 generator = std::mt19937(std::random_device{}());
        static std::uniform_real_distribution<> distribution(0, 1);

        if (distribution(generator) < mutation_rate) {
            child.mutate();
        }

        new_population[i] = child;
    }

    delete[] population;
    return new_population;
}
