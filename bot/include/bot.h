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

    // Genome from 0 to 99
    int militancy_       = random() % 100;  
    int attractiveness_  = random() % 100;
    int intelligence_    = random() % 100;
    int childern_amount_ = random() % 100;
    int children_health_ = random() % 100;

    std::vector<int*> genes_iter_;

    Bot() = delete;

    Bot(int map_size);

    Bot(const Bot* mother, const Bot* father);

    void calibrate();

    void fill_genes_iter();

    friend bool operator<(const Bot& first, const Bot& second);
};
