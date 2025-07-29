#ifndef PARALLEL_GA_RUNNINGCONFIG_H
#define PARALLEL_GA_RUNNINGCONFIG_H

class RunningConfig {
public:
    static const int gene_length = 8;
    static const int max_generation = 1000000;
    static const int population_size = 100;
    static const int cellular_row_size = 10;
    static const int cellular_col_size = population_size / cellular_row_size;
    static constexpr double mutation_rate = 0.1;
    static const int total_solution_num = 92;
};

#endif //PARALLEL_GA_RUNNINGCONFIG_H
