#include <random>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include "OpenMPRunner.h"

Chromosome OpenMPRunner::pick_parent(const Chromosome population[]) {
    // Randomly select a parent from the population
    auto *possibilities = new double[population_size];

    for (int i = 0; i < population_size; ++i) {
        possibilities[i] = population[i].get_fitness() / double(max_fitness);
    }

    thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
    double total = std::accumulate(possibilities, possibilities + population_size, 0.0);
    std::uniform_real_distribution<> distribution(0, total);
    double pick_point = distribution(generator);

    double accumulator = 0;
    for (int i = 0; i < population_size; ++i) {
        accumulator += possibilities[i];
        if (accumulator >= pick_point) {
            delete[] possibilities;
            return population[i];
        }
    }

    throw std::runtime_error("No parent found, this should not happen.");
}

Chromosome *OpenMPRunner::generate_population(const Chromosome population[]) {
    auto *new_population = new Chromosome[population_size];

#pragma omp parallel for schedule(static)
    for (int i = 0; i < population_size; ++i) {
        Chromosome x = pick_parent(population);
        Chromosome y = pick_parent(population);
        Chromosome child = x.cross_over(y);

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

void OpenMPRunner::find_solutions(const Chromosome population[]) {
#pragma omp parallel for schedule(static)
    for (int i = 0; i < population_size; ++i) {
        if (population[i].get_fitness() == max_fitness) {
#pragma omp critical
            solutions.insert(population[i]);
        }
    }
}

void OpenMPRunner::run() {
    double start = omp_get_wtime();

    auto *population = new Chromosome[population_size];

#pragma omp parallel for schedule(static)
    for (int i = 0; i < population_size; ++i) {
        Chromosome chromosome(gene_length);
        population[i] = chromosome;
    }

    while (true) {
        find_solutions(population);

        if (solutions.size() >= total_solution_num) {
            break;
        }

        population = generate_population(population);
        generation++;
    }

    double end = omp_get_wtime();
    running_time = static_cast<long long>((end - start) * 1000);
}

void OpenMPRunner::show_running_info() {
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

void OpenMPRunner::show_solutions() {
    for (const auto &solution: solutions) {
        std::cout << "Genes: ";
        solution.show_genes();
        std::cout << "Chessboard:" << std::endl;
        solution.show_chessboard();
    }
    std::cout << "Generation: " << generation << std::endl;

}
