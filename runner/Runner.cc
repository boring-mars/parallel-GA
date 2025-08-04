#include "Runner.h"

Runner::Runner()
        // Init the runner with the running configuration
        : max_generation(RunningConfig::max_generation),
          gene_length(RunningConfig::gene_length),
          max_fitness(gene_length * (gene_length - 1) / 2),
          mutation_rate(RunningConfig::mutation_rate),
          population_size(RunningConfig::population_size),
          total_solution_num(RunningConfig::total_solution_num) {
}