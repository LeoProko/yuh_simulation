#pragma once

#include <iostream>
#include <vector>
#include <list>

#include "bot.h"
#include "map.h"
#include "move.h"

class Run {
private:
    int map_size_;
    int bots_amount_;
    int days_amount_;
    Map today_map_;

    void init(std::list<Bot>& all_bots, int map_size, int bots_amount, int days_amount);

public:
    Run() = default;

    void run(int map_size, int bots_amount, int days_amount);
};
