#ifndef PARALLEL_GA_RUNNINGCONFIG_H
#define PARALLEL_GA_RUNNINGCONFIG_H

class RunningConfig {
public:
    /**
     * The length of the gene in the chromosome
     * This represents the number of queens in the N-Queens problem
     */
    static constexpr int gene_length = 8;

    /**
     * The maximum generation to run the genetic algorithm
     * When the generation reaches this number, the runner will stop
     */
    static constexpr int max_generation = 100'0000;

    /**
     * The generation number for synchronising solutions
     * This is used in the MPI runner to synchronise solutions across processes
     */
    static constexpr int sync_generation = 10'0000;

    /**
     * The size of the population in the genetic algorithm
     */
    static constexpr int population_size = 100;

    /**
     * The mutation rate for the genetic algorithm
     * The higher the mutation rate, the more exploration is done in the search space
     */
    static constexpr double mutation_rate = 0.1;

    /**
     * The total number of solutions to find
     * This represents the number of unique solutions to find in the N-Queens problem
     */
    static constexpr int total_solution_num = 92;
};

#endif //PARALLEL_GA_RUNNINGCONFIG_H
