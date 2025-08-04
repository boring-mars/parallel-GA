#include <vector>
#include <random>
#include <iostream>
#include "Chromosome.h"

Chromosome::Chromosome(int gene_len) {
    // Generate each gene randomly
    for (int i = 0; i < gene_len; ++i) {
        genes[i] = get_random_num(gene_len);
    }

    // Recompute the fitness of the chromosome
    cal_fitness();
}

int Chromosome::get_random_num(int gene_len) {
    // Init the random number generator and distribution
    thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
    thread_local static std::uniform_int_distribution<> distribution(1, gene_len);

    // Return a random number
    return distribution(generator);
}

void Chromosome::cal_fitness() {
    // Calculate the number of horizontal collisions
    int horizontal_collisions = 0;
    for (int i = 0; i < gene_len; ++i) {
        horizontal_collisions += static_cast<int> (std::count(genes, genes + gene_len, genes[i])) - 1;
    }
    horizontal_collisions /= 2;

    // Calculate the number of diagonal collisions
    std::vector<int> left_diagonal(2 * gene_len, 0);
    std::vector<int> right_diagonal(2 * gene_len, 0);

    for (int i = 0; i < gene_len; ++i) {
        left_diagonal.at(i + genes[i] - 1)++;
        right_diagonal.at(gene_len - i + genes[i] - 2)++;
    }

    int diagonal_collisions = 0;
    for (int i = 0; i < 2 * gene_len - 1; ++i) {
        if (left_diagonal.at(i) > 1) {
            diagonal_collisions += left_diagonal.at(i) - 1;
        }
        if (right_diagonal.at(i) > 1) {
            diagonal_collisions += right_diagonal.at(i) - 1;
        }
    }

    // The maximum fitness is the queens can be placed without any collisions
    int max_fitness = gene_len * (gene_len - 1) / 2;

    // The fitness is the maximum fitness minus the number of collisions
    fitness = max_fitness - horizontal_collisions - diagonal_collisions;
}

Chromosome Chromosome::cross_over(const Chromosome &other) const {
    Chromosome child;

    // Randomly select a crossover point
    int cross_over_point = get_random_num(gene_len) - 1;

    // Append genes from both parents' segments to the child
    std::copy(genes, genes + cross_over_point, child.genes);
    std::copy(other.genes + cross_over_point, other.genes + gene_len, child.genes + cross_over_point);

    // Recompute the fitness of the child chromosome
    child.cal_fitness();

    return child;
}

void Chromosome::mutate() {
    // Randomly select a mutation point
    int mutation_point = get_random_num(gene_len) - 1;

    // Randomly select a new gene value
    int new_gene_val = get_random_num(gene_len);

    // Replace the gene at the mutation point with the new value
    genes[mutation_point] = new_gene_val;

    // Recompute fitness after mutation
    cal_fitness();
}

void Chromosome::show_genes() const {
    // Print the genes of the chromosome
    for (int i = 0; i < gene_len; ++i) {
        std::cout << genes[i] << " ";
    }
    std::cout << std::endl;
}

void Chromosome::show_chessboard() const {
    // Print the chessboard representation of the chromosome
    for (int row = 0; row < gene_len; ++row) {
        for (int col = 0; col < gene_len; ++col) {
            if (genes[row] == col + 1) {
                std::cout << "Q ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

bool Chromosome::operator==(const Chromosome &other) const {
    // Compare the genes of the two chromosomes
    return std::equal(genes, genes + gene_len, other.genes);
}
