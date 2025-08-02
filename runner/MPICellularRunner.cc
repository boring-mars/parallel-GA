#include <random>
#include <mpi.h>
#include "MPICellularRunner.h"

Chromosome *MPICellularRunner::generate_population(const Chromosome *island) {
    auto *new_population = new Chromosome[island_size];

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < island_size; ++i) {
        int row = i / cellular_col_size;
        int col = i % cellular_col_size;
        Chromosome x = pick_parent_from_neighbors(island, row, col);
        Chromosome y = pick_parent_from_neighbors(island, row, col);
        Chromosome child = x.cross_over(y);

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
    MPI_Bcast(population,
              static_cast<int>(population_size * sizeof(Chromosome)),
              MPI_BYTE,
              0,
              MPI_COMM_WORLD);

    int *population_size_pre_island = new int[total_nodes];
    int base = population_size / total_nodes;
    int remainder = population_size % total_nodes;
    for (int i = 0; i < total_nodes; ++i) {
        population_size_pre_island[i] = base + (i < remainder ? 1 : 0);
    }
    island_size = population_size_pre_island[rank];

    auto *island = new Chromosome[island_size];
    int offset = std::accumulate(population_size_pre_island, population_size_pre_island + rank, 0);
    std::copy(population + offset, population + offset + island_size, island);

    delete[] population;
    delete[] population_size_pre_island;

    // Rebuild the cellular structure
    build_cellular(island_size);

    return island;
}
