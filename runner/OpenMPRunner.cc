#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include "OpenMPRunner.h"

std::mt19937 OpenMPRunner::generator = std::mt19937(std::random_device{}());

Chromosome OpenMPRunner::pick_parent(const std::vector<Chromosome> &population) {
    // Randomly select a parent from the population
    std::vector<double> possibilities(population_size);

    for (int i = 0; i < population_size; ++i) {
        possibilities.at(i) = population.at(i).get_fitness() / double(max_fitness);
    }

    double total = std::accumulate(possibilities.begin(), possibilities.end(), 0.0);
    std::uniform_real_distribution<> distribution(0, total);
    double pick_point = distribution(generator);

    double accumulator = 0;
    for (int i = 0; i < population_size; ++i) {
        accumulator += possibilities.at(i);
        if (accumulator >= pick_point) {
            return population.at(i);
        }
    }

    throw std::runtime_error("No parent found, this should not happen.");
}

std::vector<Chromosome> OpenMPRunner::generate_population(std::vector<Chromosome> &population) {
    std::vector<Chromosome> new_population;

#pragma omp parallel for schedule(static)
    for (int i = 0; i < population_size; ++i) {
        Chromosome x = pick_parent(population);
        Chromosome y = pick_parent(population);
        Chromosome child = x.cross_over(y);

        static std::uniform_real_distribution<> distribution(0, 1);

        if (distribution(generator) < mutation_rate) {
            child.mutate();
        }

#pragma omp critical
        new_population.push_back(child);
    }

    return new_population;
}

void OpenMPRunner::find_solutions(const std::vector<Chromosome> &population) {
#pragma omp parallel for schedule(static)
    for (int i = 0; i < population_size; ++i) {
        if (population.at(i).get_fitness() == max_fitness) {
#pragma omp critical
            solutions.insert(population.at(i));
        }
    }
}

void OpenMPRunner::run() {
    double start = omp_get_wtime();

    std::vector<Chromosome> population;

#pragma omp parallel for schedule(static)
    for (int i = 0; i < population_size; ++i) {
        Chromosome chromosome(gene_length);
#pragma omp critical
        population.push_back(chromosome);
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
