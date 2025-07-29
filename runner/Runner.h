#ifndef PARALLEL_GA_RUNNER_H
#define PARALLEL_GA_RUNNER_H

#include <vector>
#include "../model/Chromosome.h"

class Runner {

protected:
    int generation;
    int max_generation;
    int gene_length;
    int max_fitness;
    double mutation_rate;
    int population_size;
    int total_solution_num;

    Runner();

    virtual Chromosome pick_parent(const Chromosome population[]) = 0;

    virtual Chromosome* generate_population(const Chromosome population[]) = 0;

    virtual void find_solutions(const Chromosome population[]) = 0;

public:

    virtual void run() = 0;

    virtual void show_running_info() = 0;

    virtual void show_solutions() = 0;
};

#endif //PARALLEL_GA_RUNNER_H
