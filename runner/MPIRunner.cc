#include <random>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include <mpi.h>
#include "MPIRunner.h"

MPIRunner::MPIRunner()
        : Runner(),
          sync_generation(RunningConfig::sync_generation) {
}

Chromosome MPIRunner::pick_parent(const Chromosome island[]) const {
    // Randomly select a parent from the island
    int total = 0;

    for (int i = 0; i < island_size; ++i) {
        total += island[i].get_fitness();
    }

    thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, total);
    int pick_point = distribution(generator);

    int accumulator = 0;
    for (int i = 0; i < island_size; ++i) {
        accumulator += island[i].get_fitness();
        if (accumulator >= pick_point) {
            return island[i];
        }
    }

    throw std::runtime_error("No parent found, this should not happen.");
}

Chromosome *MPIRunner::generate_population(const Chromosome island[]) {
    auto *new_population = new Chromosome[island_size];

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < island_size; ++i) {
        Chromosome x = pick_parent(island);
        Chromosome y = pick_parent(island);
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

void MPIRunner::find_solutions(const Chromosome island[]) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < island_size; ++i) {
        if (island[i].get_fitness() == max_fitness) {
            #pragma omp critical
            local_solutions.insert(island[i]);
        }
    }
}

Chromosome *MPIRunner::sharding_population(Chromosome population[]) {
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

    return island;
}

void MPIRunner::sync_solutions() {
    int local_solution_size = static_cast<int>(local_solutions.size());
    int *solution_size_pre_island = new int[total_nodes];
    MPI_Allgather(&local_solution_size,
                  1,
                  MPI_INT,
                  solution_size_pre_island,
                  1,
                  MPI_INT,
                  MPI_COMM_WORLD);

    int *segment = new int[total_nodes];
    for (int i = 0; i < total_nodes; ++i) {
        segment[i] = static_cast<int>(solution_size_pre_island[i] * sizeof(Chromosome));
    }

    int *offset = new int[total_nodes]{0};
    for (int i = 1; i < total_nodes; ++i) {
        offset[i] = offset[i - 1] + segment[i - 1];
    }

    auto *send_buf = new Chromosome[local_solutions.size()];
    int global_solution_size = std::accumulate(solution_size_pre_island, solution_size_pre_island + total_nodes, 0);
    auto *receive_buf = new Chromosome[global_solution_size];
    std::copy(local_solutions.begin(), local_solutions.end(), send_buf);

    MPI_Allgatherv(send_buf,
                   segment[rank],
                   MPI_BYTE,
                   receive_buf,
                   segment,
                   offset,
                   MPI_BYTE,
                   MPI_COMM_WORLD);

    solutions.insert(receive_buf, receive_buf + global_solution_size);

    local_solutions.clear();

    delete[] send_buf;
    delete[] receive_buf;
    delete[] solution_size_pre_island;
    delete[] offset;
    delete[] segment;
}

void MPIRunner::run() {
    // initialize MPI environment
    MPI_Init(nullptr, nullptr);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_nodes);

    double start = MPI_Wtime();

    auto *population = new Chromosome[population_size];
    if (rank == 0) {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < population_size; ++i) {
            Chromosome chromosome(gene_length);
            population[i] = chromosome;
        }
    }

    // shard the population to each node
    auto *island = sharding_population(population);

    while (generation < max_generation && solutions.size() < total_solution_num) {
        for (int i = 0; i < sync_generation; ++i) {
            island = generate_population(island);
            find_solutions(island);
            generation++;
        }

        // gather solutions from all nodes
        sync_solutions();
    }

    delete[] island;

    double end = MPI_Wtime();
    running_time = static_cast<long long>((end - start) * 1000);

    // finalize MPI environment
    MPI_Finalize();
}

void MPIRunner::show_running_info() {
    if (rank != 0) {
        return;
    }

    std::cout << "Using " << total_nodes << " MPI nodes" << std::endl;

    #pragma omp parallel
    {
        #pragma omp single
        std::cout << "Using " << omp_get_num_threads() << " OpenMP threads" << std::endl;
    }

    std::cout << "Running with " << population_size << " chromosomes, "
              << "gene length: " << gene_length << ", "
              << "max fitness: " << max_fitness << ", "
              << "mutation rate: " << mutation_rate << std::endl;
    std::cout << "Total generations: " << generation << std::endl;
    std::cout << "Total solutions found: " << solutions.size() << std::endl;
    std::cout << "Running time: " << running_time << " ms" << std::endl;
    std::cout << "Running rate: " << static_cast<double> (running_time) / generation << " ms/generation" << std::endl;
}

void MPIRunner::show_solutions() {
    if (rank != 0) {
        return;
    }

    for (const auto &solution: solutions) {
        std::cout << "Genes: ";
        solution.show_genes();
        std::cout << "Chessboard:" << std::endl;
        solution.show_chessboard();
    }
    std::cout << "Generation: " << generation << std::endl;
}
