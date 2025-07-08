#ifndef PARALLEL_GA_RUNNER_H
#define PARALLEL_GA_RUNNER_H

#include <vector>
#include "../Chromosome.h"

class Runner {

protected:
    int generation;
    int gene_length;
    int max_fitness;
    double mutation_rate;
    int population_size;
    int total_solution_num;

    Runner();

    virtual Chromosome pick_parent(const std::vector<Chromosome> &population) = 0;

    virtual std::vector<Chromosome> generate_population(std::vector<Chromosome> &population) = 0;

    virtual std::vector<Chromosome> find_solutions(const std::vector<Chromosome> &population) = 0;

public:

    virtual void run() = 0;

};

#endif //PARALLEL_GA_RUNNER_H
