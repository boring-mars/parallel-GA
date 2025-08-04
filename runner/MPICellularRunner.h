#ifndef PARALLEL_GA_MPICELLULARRUNNER_H
#define PARALLEL_GA_MPICELLULARRUNNER_H

#include "MPIRunner.h"
#include "CellularRunner.h"

/**
 * Runner for the cellular genetic algorithm using MPI and OpenMP
 * The numbers of processes and threads are determined by the running environment
 */
class MPICellularRunner : public MPIRunner, public CellularRunner {

protected:
    Chromosome *generate_population(const Chromosome population[]) override;

    Chromosome *sharding_population(Chromosome population[]) override;

public:
    MPICellularRunner() : Runner(), CellularRunner(), MPIRunner() {};
};

#endif //PARALLEL_GA_MPICELLULARRUNNER_H
