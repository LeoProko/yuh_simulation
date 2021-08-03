#pragma once

#include <deque>

#include "bot.h"
#include "position.h"

class Cell {
private:
    void reproduce();

    void split_food();

    int total_coef_ = 0;

public:
    int bot_counter_ = 0;
    int food_counter_ = 0;

    std::deque<Bot*> bots_;

    Cell() = default;

    void do_all();

    void add_bot(Bot& bot);
};
