#pragma once

#include "behaviors.h"

struct Cell {
    int bot_counter_ = 0;
    int bot_power_counter_ = 0;
    int food_counter_ = 0;

    Cell() = default;

    void DoAll() {
        // Reproduce()
        // SplitFood()
    }
};
