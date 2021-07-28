#pragma once

#include <cstdlib>
#include <algorithm>

#include "position.h"

class Bot {
public:
    Position position_;

    // Genome
    int health_ = 100;  // from 0 to 100
    int food_amount_ = 1;  // from 0 to MAX_INT
    int militancy_ = std::rand() % 101;  // from 0 to 100
    int attractiveness_ = std::rand() % 101;
    int intelligence_ = std::rand() % 101;
    
    Bot() = delete;

    Bot(int map_size);

    Bot(Bot& mother, Bot& father);
};
