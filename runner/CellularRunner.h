#ifndef PARALLEL_GA_CELLULARRUNNER_H
#define PARALLEL_GA_CELLULARRUNNER_H


#include "Runner.h"

class CellularRunner : public virtual Runner {

protected:
    int cellular_row_size = 10;
    int cellular_col_size = population_size / cellular_row_size;

    Chromosome pick_parent_from_neighbors(const Chromosome population[], int row, int col);

public:
    CellularRunner() : Runner() {};
};


#endif //PARALLEL_GA_CELLULARRUNNER_H
