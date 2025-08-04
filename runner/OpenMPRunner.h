#ifndef PARALLEL_GA_OPENMPRUNNER_H
#define PARALLEL_GA_OPENMPRUNNER_H

#include "Runner.h"

/**
 * Runner for the genetic algorithm using OpenMP
 * The number of threads is determined by the running environment
 */
class OpenMPRunner : public virtual Runner {

protected:
    Chromosome pick_parent(const Chromosome population[]) const override;

    Chromosome *generate_population(const Chromosome population[]) override;

    void find_solutions(const Chromosome population[]) override;

public:
    OpenMPRunner() : Runner() {};

    void run() override;

    void show_running_info() override;

    void show_solutions() override;
};


#endif //PARALLEL_GA_OPENMPRUNNER_H
