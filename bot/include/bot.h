#pragma once

#include <algorithm>
#include <random>

#include "position.h"
#include "rand.h"

class Bot {
public:
    Position position_;
    const int mutation = 10;

    // Characteristics
    int health_ = 100;  // from 0 to 100

    // Genome from 0 to 99
    int militancy_       = Rand::random_() % 100;
    int attractiveness_  = Rand::random_() % 100;
    int intelligence_    = Rand::random_() % 100;
    int children_amount_ = Rand::random_() % 10;
    int children_health_ = Rand::random_() % 100;

    Bot() = delete;

    Bot(int map_size);

    Bot(const Bot* mother, const Bot* father);

    void calibrate();

    friend bool operator<(const Bot& first, const Bot& second);
};
