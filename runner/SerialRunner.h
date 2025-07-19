#ifndef PARALLEL_GA_SERIALRUNNER_H
#define PARALLEL_GA_SERIALRUNNER_H

#include <vector>
#include <unordered_set>
#include <random>
#include "Runner.h"

class SerialRunner : Runner {

private:
    static std::mt19937 generator;
    std::unordered_set<Chromosome> solutions;

protected:
    Chromosome pick_parent(const std::vector<Chromosome> &population) override;

    std::vector<Chromosome> generate_population(std::vector<Chromosome> &population) override;

    void find_solutions(const std::vector<Chromosome> &population) override;

public:
    SerialRunner() : Runner() {};

    void run() override;
};


#endif //PARALLEL_GA_SERIALRUNNER_H
