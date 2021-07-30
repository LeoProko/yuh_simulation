#pragma once

#include <vector>

#include "bot.h"
#include "position.h"

class Cell {
private:
    void reproduce();

    void split_food();

public:
    int bot_counter_ = 0;
    int food_counter_ = 0;

    std::vector<Bot> bots_;

    Cell() = default;

    void do_all();
};
