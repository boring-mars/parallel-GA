#include "Runner.h"

Runner::Runner() {
    generation = 0;
    gene_length = 8;
    max_fitness = gene_length * (gene_length - 1) / 2;
    mutation_rate = 0.1;
    population_size = 50;
    total_solution_num = 92;
}
