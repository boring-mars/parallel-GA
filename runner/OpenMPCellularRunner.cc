#include <random>
#include "OpenMPCellularRunner.h"

Chromosome *OpenMPCellularRunner::generate_population(const Chromosome population[]) {
    auto *new_population = new Chromosome[population_size];

    // Generate equal number of chromosomes for the new population
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < population_size; ++i) {
        // Compute the row and column indices in the cellular grid
        int row = i / cellular_col_size;
        int col = i % cellular_col_size;

        // Apply crossover between two parents from the 3x3 neighborhood
        Chromosome x = pick_parent_from_neighbors(population, row, col);
        Chromosome y = pick_parent_from_neighbors(population, row, col);
        Chromosome child = x.cross_over(y);

        // Apply mutation with a certain mutation rate
        thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
        thread_local static std::uniform_real_distribution<> distribution(0, 1);

        if (distribution(generator) < mutation_rate) {
            child.mutate();
        }

        new_population[i] = child;
    }

    delete[] population;
    return new_population;
}