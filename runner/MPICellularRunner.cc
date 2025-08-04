#include <random>
#include <mpi.h>
#include "MPICellularRunner.h"

Chromosome *MPICellularRunner::generate_population(const Chromosome *island) {
    auto *new_population = new Chromosome[island_size];

    // Generate equal number of chromosomes for the new population
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < island_size; ++i) {
        // Compute the row and column indices in the cellular grid
        int row = i / cellular_col_size;
        int col = i % cellular_col_size;

        // Apply crossover between two parents from the 3x3 neighborhood
        Chromosome x = pick_parent_from_neighbors(island, row, col);
        Chromosome y = pick_parent_from_neighbors(island, row, col);
        Chromosome child = x.cross_over(y);

        // Apply mutation with a certain mutation rate
        thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
        thread_local static std::uniform_real_distribution<> distribution(0, 1);

        if (distribution(generator) < mutation_rate) {
            child.mutate();
        }

        new_population[i] = child;
    }

    delete[] island;
    return new_population;
}

Chromosome *MPICellularRunner::sharding_population(Chromosome population[]) {
    // Broadcast the whole population to all nodes
    MPI_Bcast(population,
              static_cast<int>(population_size * sizeof(Chromosome)),
              MPI_BYTE,
              0,
              MPI_COMM_WORLD);

    // Compute the size of the island for each node
    int *population_size_pre_island = new int[total_nodes];
    int base = population_size / total_nodes;
    int remainder = population_size % total_nodes;
    for (int i = 0; i < total_nodes; ++i) {
        population_size_pre_island[i] = base + (i < remainder ? 1 : 0);
    }
    island_size = population_size_pre_island[rank];

    // Create the island for the current node
    auto *island = new Chromosome[island_size];
    int offset = std::accumulate(population_size_pre_island, population_size_pre_island + rank, 0);
    std::copy(population + offset, population + offset + island_size, island);

    delete[] population;
    delete[] population_size_pre_island;

    // Rebuild the cellular gird for the island
    build_cellular(island_size);

    return island;
}
