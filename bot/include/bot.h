#pragma once

#include <algorithm>
#include <random>

#include "position.h"

class Bot {
public:
    Position position_;
    int genes_amount_ = 5;
    std::mt19937 random;

    // Characteristics
    int health_ = 100;  // from 0 to 100

    // Genome
    int militancy_ = random() % 101;  // from 0 to 100
    int attractiveness_ = random() % 101;
    int intelligence_ = random() % 101;
    int childern_amount_ = random() % 101;
    int children_health_ = random() % 101;

    std::vector<int*> genes_iter_;

    Bot() = delete;

    Bot(int map_size);

    Bot(const Bot& mother, const Bot& father);

    void calibrate();

    void fill_genes_iter();

    friend bool operator<(const Bot& first, const Bot& second);
};
