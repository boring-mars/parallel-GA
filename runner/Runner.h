#ifndef PARALLEL_GA_RUNNER_H
#define PARALLEL_GA_RUNNER_H

#include <unordered_set>
#include "../model/Chromosome.h"

/**
 * Base class for the genetic algorithm runner
 * Defines the core functions and properties
 */
class Runner {

protected:
    /**
     * Current processing generation number
     */
    int generation = 0;

    /**
     * Total running time in milliseconds
     */
    long long running_time = 0;

    /**
     * Final solutions found
     */
    std::unordered_set<Chromosome> solutions;

    /**
     * The length of the genes
     * This represents the number of queens in the N-Queens problem
     */
    int gene_length;

    /**
     * Maximum number of generations to run
     */
    int max_generation;

    /**
     * Maximum fitness value
     */
    int max_fitness;

    /**
     * The rate of mutation
     * The higher the mutation rate, the more exploration is done in the search space
     */
    double mutation_rate;

    /**
     * The size of the population
     */
    int population_size;

    /**
     * The number of solutions to find
     */
    int total_solution_num;

    /**
     * Default constructor to load the running configuration
     */
    Runner();

    /**
     * Pick a parent from the population using roulette algorithm
     * @param population The population to pick from
     * @return A chromosome selected as a parent
     */
    virtual Chromosome pick_parent(const Chromosome population[]) const = 0;

    /**
     * Generate a new population based on the current population
     * @param population The last population
     * @return The new population
     */
    virtual Chromosome *generate_population(const Chromosome population[]) = 0;

    /**
     * Find solutions in the population
     * The solution is a chromosome with maximum fitness
     * @param population The population to find solutions in
     */
    virtual void find_solutions(const Chromosome population[]) = 0;

public:

    /**
     * Core function to run the genetic algorithm
     */
    virtual void run() = 0;

    /**
     * Show the metadata of the run
     */
    virtual void show_running_info() = 0;

    /**
     * Show all the solutions found
     * Represent in genes and chessboard format
     */
    virtual void show_solutions() = 0;
};

#endif //PARALLEL_GA_RUNNER_H
