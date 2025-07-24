#ifndef PARALLEL_GA_RUNNINGCONFIG_H
#define PARALLEL_GA_RUNNINGCONFIG_H

class RunningConfig {
public:
    static const int gene_length = 8;
    static const int population_size = 50;
    static constexpr double mutation_rate = 0.1;
    static const int total_solution_num = 50;
};

#endif //PARALLEL_GA_RUNNINGCONFIG_H
