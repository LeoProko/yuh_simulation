#pragma once

#include <cstdlib>
#include <set>

#include "position.h"

class Bot {
public:
    Position position_;

    // Genome
    int health_ = 100;  // from 0 to 100
    int food_amount_ = 1;  // from 0 to MAX_INT
    int militancy_ = 50;  // from 0 to 100

    Bot() = delete;

    Bot(int size);
};
