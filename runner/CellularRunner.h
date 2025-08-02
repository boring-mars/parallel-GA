#ifndef PARALLEL_GA_CELLULARRUNNER_H
#define PARALLEL_GA_CELLULARRUNNER_H

#include "Runner.h"

class CellularRunner : public virtual Runner {

protected:
    int cellular_row_size;
    int cellular_col_size;

    CellularRunner();

    void build_cellular(int population_size);

    Chromosome pick_parent_from_neighbors(const Chromosome population[], int row, int col) const;
};


#endif //PARALLEL_GA_CELLULARRUNNER_H
