#ifndef PARALLEL_GA_RUNNINGCONFIG_H
#define PARALLEL_GA_RUNNINGCONFIG_H

class RunningConfig {
public:
    static constexpr int gene_length = 8;
    static constexpr int max_generation = 100000;
    static constexpr int sync_generation = 10000;
    static constexpr int population_size = 100;
    static constexpr int cellular_row_size = 10;
    static constexpr int cellular_col_size = population_size / cellular_row_size;
    static constexpr double mutation_rate = 0.1;
    static constexpr int total_solution_num = 92;
};

#endif //PARALLEL_GA_RUNNINGCONFIG_H
