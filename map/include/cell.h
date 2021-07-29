#pragma once

#include <vector>
#include "bot.h"


struct Cell {
    int bot_counter_ = 0;
    int food_counter_ = 0;

    std::vector<Bot*> queue;

    Cell() = default;
};
