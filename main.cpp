#include <vector>
#include <iostream>
#include <numeric>
#include <random>
#include "Chromosome.h"

int generation = 0;
const int gene_length = 8;
const double mutation_rate = 0.1;
int population_size = 100;
int total_solution_num = 92;

static std::mt19937 generator = std::mt19937(std::random_device{}());

Chromosome pick_parent(const std::vector<Chromosome> &population) {
    // Randomly select a parent from the population
    std::vector<double> possibilities;
    int max_fitness = gene_length * (gene_length - 1) / 2;

    for (const auto &chromosome: population) {
        possibilities.push_back(chromosome.get_fitness() / double(max_fitness));
    }

    double total = std::accumulate(possibilities.begin(), possibilities.end(), 0.0);
    std::uniform_real_distribution<> distribution(0, total);
    double pick_point = distribution(generator);

    double accumulator = 0;
    for (int i = 0; i < population.size(); ++i) {
        accumulator += possibilities.at(i);
        if (accumulator >= pick_point) {
            return population.at(i);
        }
    }

    throw std::runtime_error("No parent found, this should not happen.");
}

std::vector<Chromosome> generate_population(std::vector<Chromosome> &population) {
    std::vector<Chromosome> new_population;

    for (int i = 0; i < population_size; ++i) {
        Chromosome x = pick_parent(population);
        Chromosome y = pick_parent(population);
        Chromosome child = x.cross_over(y);

        static std::uniform_real_distribution<> distribution(0, 1);

        if (distribution(generator) < mutation_rate) {
            child.mutate();
        }

        new_population.push_back(child);
    }

    return new_population;
}

const Chromosome *find_solution(const std::vector<Chromosome> &population) {
    for (const auto &chromosome: population) {
        int max_fitness = gene_length * (gene_length - 1) / 2;
        if (chromosome.get_fitness() == max_fitness) {
            return &chromosome;
        }
    }

    return nullptr;
}


int main() {
    std::vector<Chromosome> population;
    for (int i = 0; i < population_size; ++i) {
        Chromosome chromosome(gene_length);
        population.push_back(chromosome);
    }

    std::vector<Chromosome> solutions;
    const Chromosome *solution = find_solution(population);
    if (solution) {
        std::cout << "Solution found in generation " << generation << std::endl;
        solutions.push_back(*solution);
    }

    while (solutions.size() < total_solution_num) {
        population = generate_population(population);

        solution = find_solution(population);
        if (solution) {
            auto same = std::find(solutions.begin(), solutions.end(), *solution);
            if (same != solutions.end()) {
                continue;
            }
            std::cout << "Solution found in generation " << generation << std::endl;
            solutions.push_back(*solution);
        }

        generation++;
    }

    for (const auto &solution: solutions) {
        std::cout << "Genes: ";
        solution.show_genes();
        std::cout << "Chessboard:" << std::endl;
        solution.show_chessboard();
    }

    return 0;
}
