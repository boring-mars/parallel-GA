#ifndef PARALLEL_GA_SERIALCELLULARRUNNER_H
#define PARALLEL_GA_SERIALCELLULARRUNNER_H

#include "SerialRunner.h"
#include "CellularRunner.h"

/**
 * Runner for the cellular genetic algorithm in serial mode
 */
class SerialCellularRunner : public SerialRunner, public CellularRunner {

protected:
    Chromosome *generate_population(const Chromosome population[]) override;

public:
    SerialCellularRunner() : Runner(), CellularRunner(), SerialRunner() {};
};


#endif //PARALLEL_GA_SERIALCELLULARRUNNER_H
