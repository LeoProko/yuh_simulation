#pragma once

#include "bot.h"
#include "position.h"

class Cell {
public:
    int bot_counter_ = 0;
    int food_counter_ = 0;

    std::set<Bot> bots_;

    Cell() = default;

    void do_all();

    void reproduce();

    void split_food();
};
