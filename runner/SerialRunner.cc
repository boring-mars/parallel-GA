#include <random>
#include <iostream>
#include <chrono>
#include "SerialRunner.h"

Chromosome SerialRunner::pick_parent(const Chromosome population[]) const {
    // Compute the total fitness of the population
    int total = 0;
    for (int i = 0; i < population_size; ++i) {
        total += population[i].get_fitness();
    }

    // Randomly select a point in the fitness distribution
    thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, total);
    int pick_point = distribution(generator);

    // Select a parent from the population using roulette selection
    int accumulator = 0;
    for (int i = 0; i < population_size; ++i) {
        accumulator += population[i].get_fitness();
        if (accumulator >= pick_point) {
            return population[i];
        }
    }

    throw std::runtime_error("No parent found, this should not happen.");
}

Chromosome *SerialRunner::generate_population(const Chromosome population[]) {
    auto *new_population = new Chromosome[population_size];

    // Generate equal number of chromosomes for the new population
    for (int i = 0; i < population_size; ++i) {
        // Apply crossover between two parents
        Chromosome x = pick_parent(population);
        Chromosome y = pick_parent(population);
        Chromosome child = x.cross_over(y);

        // Apply mutation with a certain mutation rate
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

void SerialRunner::find_solutions(const Chromosome population[]) {
    // Find solutions in the population by checking for maximum fitness
    for (int i = 0; i < population_size; ++i) {
        if (population[i].get_fitness() == max_fitness) {
            solutions.insert(population[i]);
        }
    }
}

void SerialRunner::run() {
    // Record the start time of the run
    auto start = std::chrono::high_resolution_clock::now();

    // Init the population with random chromosomes
    auto *population = new Chromosome[population_size];
    for (int i = 0; i < population_size; ++i) {
        Chromosome chromosome(gene_length);
        population[i] = chromosome;
    }

    // Run the genetic algorithm
    while (generation < max_generation) {
        // Find solutions in the current population
        find_solutions(population);

        // Check the number of solutions found
        if (solutions.size() >= total_solution_num) {
            break;
        }

        // Generate a new population and replace the old one
        population = generate_population(population);
        generation++;
    }

    delete[] population;

    // Record the end time of the run and calculate the running time
    auto end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void SerialRunner::show_running_info() {
    // Show the metadata of the run
    std::cout << "Running with " << population_size << " chromosomes, "
              << "gene length: " << gene_length << ", "
              << "max fitness: " << max_fitness << ", "
              << "mutation rate: " << mutation_rate << std::endl;
    std::cout << "Total generations: " << generation << std::endl;
    std::cout << "Total solutions found: " << solutions.size() << std::endl;
    std::cout << "Running time: " << running_time << " ms" << std::endl;
    std::cout << "Running rate: " << static_cast<double> (running_time) / generation << " ms/generation" << std::endl;
}

void SerialRunner::show_solutions() {
    // Show all the solutions found in genes and chessboard format
    for (const auto &solution: solutions) {
        std::cout << "Genes: ";
        solution.show_genes();
        std::cout << "Chessboard:" << std::endl;
        solution.show_chessboard();
    }
    std::cout << "Generation: " << generation << std::endl;
}
