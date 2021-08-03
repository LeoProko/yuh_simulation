#pragma once

#include <algorithm>
#include <random>

#include "position.h"

class Bot {
public:
    Position position_;
    int genes_amount_ = 5;
    std::vector<int*> genes_iter_;

    // Characteristics
    int health_ = 100;  // from 0 to 100

    // Genome from 0 to 99
    int militancy_       = random() % 100;  
    int attractiveness_  = random() % 100;
    int intelligence_    = random() % 100;
    int children_amount_ = 4;
    int children_health_ = random() % 100;

    Bot() = delete;

    Bot(int map_size, std::mt19937& random);

    Bot(const Bot* mother, const Bot* father);

    void calibrate();

    void fill_genes_iter();

    friend bool operator<(const Bot& first, const Bot& second);
};
