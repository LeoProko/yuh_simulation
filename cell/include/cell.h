#pragma once

#include <deque>
#include <list>
#include <mutex>

#include "bot.h"
#include "parameters.h"
#include "position.h"

class Cell {
private:
    void reproduce(std::list<Bot>& all_bots);

    void split_food();

    void share_food();

    void fight();

    double total_collect_coeff_ = 0.;

    std::mutex* move_mutex;

public:
    int bot_counter_ = 0;
    int food_counter_ = 0;
    bool is_enemy_ = false;

    std::deque<Bot*> bots_in_cell_;

    Cell() = default;

    Cell(const Cell&);

    ~Cell();

    void do_all(std::list<Bot>& bots);

    void altruists_activation();

    void enemy_activation();

    void add_bot(Bot& bot);
};
