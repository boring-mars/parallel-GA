#ifndef PARALLEL_GA_MPIRUNNER_H
#define PARALLEL_GA_MPIRUNNER_H

#include <unordered_set>
#include "Runner.h"

/**
 * Runner for the genetic algorithm using MPI and OpenMP
 * The numbers of processes and threads are determined by the running environment
 */
class MPIRunner : public virtual Runner {

protected:
    /**
     * The size of the island
     * The island is a subset of the population processed by a MPI process
     */
    int island_size = 0;

    /**
     * The index of the current MPI process
     */
    int rank = 0;

    /**
     * The total number of MPI processes
     */
    int total_nodes = 0;

    /**
     * The generation number for synchronising solutions
     */
    int sync_generation;

    /**
     * The local solutions found by the current MPI process
     */
    std::unordered_set<Chromosome> local_solutions;

    Chromosome pick_parent(const Chromosome population[]) const override;

    Chromosome *generate_population(const Chromosome population[]) override;

    void find_solutions(const Chromosome population[]) override;

    /**
     * Sharding the population into islands and scatter across the MPI processes
     * @param population The whole population to shard
     * @return The island for the current MPI process
     */
    virtual Chromosome *sharding_population(Chromosome population[]);

    /**
     * Gather the local solutions from all MPI processes
     */
    void sync_solutions();

public:
    MPIRunner();

    void run() override;

    void show_running_info() override;

    void show_solutions() override;
};


#endif //PARALLEL_GA_MPIRUNNER_H
