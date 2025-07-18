#ifndef PARALLEL_GA_OPENMPRUNNER_H
#define PARALLEL_GA_OPENMPRUNNER_H

#include <vector>
#include <random>
#include "Runner.h"

class OpenMPRunner : Runner {

private:
    static std::mt19937 generator;

protected:
    Chromosome pick_parent(const std::vector<Chromosome> &population) override;

    std::vector<Chromosome> generate_population(std::vector<Chromosome> &population) override;

    std::vector<Chromosome> find_solutions(const std::vector<Chromosome> &population) override;

public:
    OpenMPRunner() : Runner() {};

    void run() override;

};


#endif //PARALLEL_GA_OPENMPRUNNER_H
