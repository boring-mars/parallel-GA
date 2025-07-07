#ifndef PARALLEL_GA_CHROMOSOME_H
#define PARALLEL_GA_CHROMOSOME_H


class Chromosome {
private:
    std::vector<int> genes;
    int gene_len;
    int fitness;

    Chromosome();

    static int get_random_num(int gene_len);

    void cal_fitness();

public:
    explicit Chromosome(int gene_len);

    int get_fitness() const {
        return fitness;
    }

    Chromosome cross_over(const Chromosome &other) const;

    void mutate();

    void show_genes() const;

    void show_chessboard() const;
};


#endif //PARALLEL_GA_CHROMOSOME_H
