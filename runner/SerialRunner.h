#ifndef PARALLEL_GA_SERIALRUNNER_H
#define PARALLEL_GA_SERIALRUNNER_H

#include <vector>
#include <unordered_set>
#include <random>
#include "Runner.h"

class SerialRunner : public virtual Runner {

protected:
    std::unordered_set<Chromosome> solutions;
    long long running_time;

    Chromosome pick_parent(const Chromosome population[]) const override;

    Chromosome *generate_population(const Chromosome population[]) override;

    void find_solutions(const Chromosome population[]) override;

public:
    SerialRunner() : Runner() {};

    void run() override;

    void show_running_info() override;

    void show_solutions() override;
};


#endif //PARALLEL_GA_SERIALRUNNER_H
