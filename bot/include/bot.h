#pragma once

#include <cstdlib>
#include <algorithm>

#include "position.h"

class Bot {
public:
    Position position_;

    int genes_amount_ = 5;

    // Characteristics
    int health_ = 100;  // from 0 to 100

    // Genome
    int militancy_ = std::rand() % 101;  // from 0 to 100
    int attractiveness_ = std::rand() % 101;
    int intelligence_ = std::rand() % 101;
    int childern_amount_ = std::rand() % 101;
    int children_health_ = std::rand() % 101;

    Bot() = delete;

    Bot(int map_size);

    Bot(const Bot& mother, const Bot& father);

    void calibrate();
};
