#ifndef PARALLEL_GA_MPICELLULARRUNNER_H
#define PARALLEL_GA_MPICELLULARRUNNER_H

#include "MPIRunner.h"
#include "CellularRunner.h"

class MPICellularRunner : public MPIRunner, public CellularRunner {

protected:
    Chromosome *generate_population(const Chromosome population[]) override;

    Chromosome *sharding_population(Chromosome population[]) override;

public:
    MPICellularRunner() : Runner(), CellularRunner(), MPIRunner() {};
};

#endif //PARALLEL_GA_MPICELLULARRUNNER_H
