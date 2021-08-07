#pragma once

#include <deque>
#include <list>

#include "bot.h"
#include "parameters.h"
#include "position.h"

class Cell {
private:
    void reproduce(std::list<Bot>& all_bots);

    void split_food();

    double total_coef_ = 0.;

public:
    int bot_counter_ = 0;
    int food_counter_ = 0;
    bool is_enemy_ = false;

    std::deque<Bot*> bots_in_cell_;

    Cell() = default;

    void do_all(std::list<Bot>& bots);

    void clean();

    void altruists_activation();

    void enemy_activation();

    void add_bot(Bot& bot);
};
