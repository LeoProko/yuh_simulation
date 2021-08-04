#pragma once

#include <deque>
#include <list>

#include "bot.h"
#include "position.h"

class Cell {
private:
    void reproduce(std::list<Bot>& all_bots);

    void split_food();

    double total_coef_ = 0.;

public:
    int bot_counter_ = 0;
    int food_counter_ = 0;

    std::deque<Bot*> bots_;

    Cell() = default;

    void do_all(std::list<Bot>& all_bots);

    void add_bot(Bot& bot);
};
