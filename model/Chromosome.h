#ifndef PARALLEL_GA_CHROMOSOME_H
#define PARALLEL_GA_CHROMOSOME_H

#include <vector>
#include "../RunningConfig.h"

struct Chromosome {
private:
    int genes[RunningConfig::gene_length];
    int gene_len = RunningConfig::gene_length;
    int fitness;

    friend struct std::hash<Chromosome>;

    static int get_random_num(int gene_len);

    void cal_fitness();

public:
    Chromosome() = default;

    explicit Chromosome(int gene_len);

    int get_fitness() const {
        return fitness;
    }

    Chromosome cross_over(const Chromosome &other) const;

    void mutate();

    void show_genes() const;

    void show_chessboard() const;

    bool operator==(const Chromosome &other) const;
};

namespace std {
    template<>
    struct hash<Chromosome> {
        std::size_t operator()(const Chromosome &c) const {
            std::size_t seed = c.gene_len;
            for (int i = 0; i < c.gene_len; ++i) {
                seed ^= std::hash<int>()(c.genes[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

#endif //PARALLEL_GA_CHROMOSOME_H
