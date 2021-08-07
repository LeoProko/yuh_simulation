#pragma once

#include <algorithm>

#include "parameters.h"
#include "position.h"

class Bot {
public:
    Position position_;
    int lifetime_ = 0;
    int genes_amount_ = 4;

    // Characteristics
    int health_ = 100;  // from 0 to 100

    // Genome from 0 to 99
    int militancy_       = parameters::random() % 100;
    int intelligence_    = parameters::random() % 100;
    int children_amount_ = parameters::random() % 10;
    int children_health_ = parameters::random() % 100;

    Bot();

    Bot(const Bot* mother, const Bot* father);

    void calibrate();

    friend bool operator<(const Bot& first, const Bot& second);
};
