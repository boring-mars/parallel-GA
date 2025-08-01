#ifndef PARALLEL_GA_MPIRUNNER_H
#define PARALLEL_GA_MPIRUNNER_H

#include <unordered_set>
#include "Runner.h"

class MPIRunner : public virtual Runner {

protected:
    int island_size = 0;
    int rank = 0;
    int total_nodes = 0;
    int sync_generation;
    std::unordered_set<Chromosome> local_solutions;

    Chromosome pick_parent(const Chromosome population[]) const override;

    Chromosome *generate_population(const Chromosome population[]) override;

    void find_solutions(const Chromosome population[]) override;

    Chromosome *sharding_population(Chromosome population[]);

    void sync_solutions();

public:
    MPIRunner();

    void run() override;

    void show_running_info() override;

    void show_solutions() override;
};


#endif //PARALLEL_GA_MPIRUNNER_H
