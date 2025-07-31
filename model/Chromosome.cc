#include <vector>
#include <random>
#include <iostream>
#include "Chromosome.h"

Chromosome::Chromosome(int gene_len) {
    for (int i = 0; i < gene_len; ++i) {
        genes[i] = get_random_num(gene_len);
    }

    cal_fitness();
}

int Chromosome::get_random_num(int gene_len) {
    thread_local static std::mt19937 generator = std::mt19937(std::random_device{}());
    thread_local static std::uniform_int_distribution<> distribution(1, gene_len);

    return distribution(generator);
}

void Chromosome::cal_fitness() {
    int horizontal_collisions = 0;
    for (int i = 0; i < gene_len; ++i) {
        horizontal_collisions += (int) std::count(genes, genes + gene_len, genes[i]) - 1;
    }
    horizontal_collisions /= 2;

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

    int max_fitness = gene_len * (gene_len - 1) / 2;

    fitness = max_fitness - horizontal_collisions - diagonal_collisions;
}

Chromosome Chromosome::cross_over(const Chromosome &other) const {
    Chromosome child;

    int cross_over_point = get_random_num(gene_len) - 1;
    std::copy(genes, genes + cross_over_point, child.genes);
    std::copy(other.genes + cross_over_point, other.genes + gene_len, child.genes + cross_over_point);

    child.cal_fitness();

    return child;
}

void Chromosome::mutate() {
    int mutation_point = get_random_num(gene_len) - 1;

    // Randomly select a new gene value
    int new_gene_val = get_random_num(gene_len);

    // Replace the gene at the mutation point with the new value
    genes[mutation_point] = new_gene_val;

    // Recalculate fitness after mutation
    cal_fitness();
}

void Chromosome::show_genes() const {
    for (int i = 0; i < gene_len; ++i) {
        std::cout << genes[i] << " ";
    }
    std::cout << std::endl;
}

void Chromosome::show_chessboard() const {
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
    return std::equal(genes, genes + gene_len, other.genes);
}
