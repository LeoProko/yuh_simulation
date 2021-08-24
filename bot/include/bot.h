#pragma once

#include <algorithm>

#include "parameters.h"
#include "position.h"

class Bot {
public:
    Position position_;
    const int genes_amount_ = 6;

    // Characteristics
    int health_ = 100;  // from 0 to 100
    int lifetime_ = 0;

    // Genome from 0 to 99
    int collect_              = parameters::random() % 100;
    int militancy_            = parameters::random() % 100;
    int intelligence_         = parameters::random() % 100;
    int vision_               = parameters::random() % 100;
    int children_amount_      = parameters::random() % 100;
    int children_health_      = parameters::random() % 100;

    bool is_altruist_         = false;
    bool is_greenbeared_      = false;
    bool is_protected_        = false;

    Bot();

    Bot(const Bot* mother, const Bot* father);

    void calibrate();

    friend bool operator<(const Bot& first, const Bot& second);
};
