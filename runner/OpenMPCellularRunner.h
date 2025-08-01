#ifndef PARALLEL_GA_OPENMPCELLULARRUNNER_H
#define PARALLEL_GA_OPENMPCELLULARRUNNER_H

#include "OpenMPRunner.h"
#include "CellularRunner.h"

class OpenMPCellularRunner : public OpenMPRunner, public CellularRunner {

protected:
    Chromosome *generate_population(const Chromosome population[]) override;

public:
    OpenMPCellularRunner() : Runner(), CellularRunner(), OpenMPRunner() {};
};


#endif //PARALLEL_GA_OPENMPCELLULARRUNNER_H
