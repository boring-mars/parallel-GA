#ifndef PARALLEL_GA_SERIALRUNNER_H
#define PARALLEL_GA_SERIALRUNNER_H

#include <vector>
#include <random>
#include "Runner.h"

class SerialRunner : public Runner {

private:
    static std::mt19937 generator;

protected:
    Chromosome pick_parent(const std::vector<Chromosome> &population) override;

    std::vector<Chromosome> generate_population(std::vector<Chromosome> &population) override;

    std::vector<Chromosome> find_solutions(const std::vector<Chromosome> &population) override;

public:
    SerialRunner() : Runner() {};

    void run() override;
};


#endif //PARALLEL_GA_SERIALRUNNER_H
