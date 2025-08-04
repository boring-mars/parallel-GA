#ifndef PARALLEL_GA_CELLULARRUNNER_H
#define PARALLEL_GA_CELLULARRUNNER_H

#include "Runner.h"

/**
 * Runner for the cellular genetic algorithm
 * This runner can't be used independently
 */
class CellularRunner : public virtual Runner {

protected:
    /**
     * The row number of the cellular grid
     */
    int cellular_row_size;

    /**
     * The column number of the cellular grid
     */
    int cellular_col_size;

    /**
     * Default constructor to init the cellular grid size
     */
    CellularRunner();

    /**
     * Build the cellular grid with the given population size
     * Pick the size of the grid to be as close to a square as possible
     * @param population_size The size of the population
     */
    void build_cellular(int population_size);

    /**
     * Pick a parent from the 3x3 neighborhood of the given cell
     * @param population The population to pick from
     * @param row The row index of the cell
     * @param col The column index of the cell
     * @return A chromosome selected as a parent
     */
    Chromosome pick_parent_from_neighbors(const Chromosome population[], int row, int col) const;
};


#endif //PARALLEL_GA_CELLULARRUNNER_H
