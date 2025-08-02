#ifndef PARALLEL_GA_RUNNINGCONFIG_H
#define PARALLEL_GA_RUNNINGCONFIG_H

class RunningConfig {
public:
    static constexpr int gene_length = 8;
    static constexpr int max_generation = 100'0000;
    static constexpr int sync_generation = 10'0000;
    static constexpr int population_size = 1000;
    static constexpr double mutation_rate = 0.1;
    static constexpr int total_solution_num = 92;
};

#endif //PARALLEL_GA_RUNNINGCONFIG_H
