#include "Runner.h"
#include "../RunningConfig.h"

Runner::Runner() {
    generation = 0;
    gene_length = RunningConfig::gene_length;
    max_fitness = gene_length * (gene_length - 1) / 2;
    mutation_rate = RunningConfig::mutation_rate;
    population_size = RunningConfig::population_size;
    total_solution_num = RunningConfig::total_solution_num;
}
