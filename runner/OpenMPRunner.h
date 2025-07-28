#ifndef PARALLEL_GA_OPENMPRUNNER_H
#define PARALLEL_GA_OPENMPRUNNER_H

#include <vector>
#include <unordered_set>
#include <random>
#include "Runner.h"

class OpenMPRunner : public virtual Runner {

protected:
    std::unordered_set<Chromosome> solutions;
    long long running_time;

    Chromosome pick_parent(const Chromosome population[]) override;

    Chromosome* generate_population(const Chromosome population[]) override;

    void find_solutions(const Chromosome population[]) override;

public:
    OpenMPRunner() : Runner() {};

    void run() override;

    void show_running_info() override;

    void show_solutions() override;
};


#endif //PARALLEL_GA_OPENMPRUNNER_H
