#pragma once

#include <iostream>
#include <list>
#include <vector>

#include "bot.h"
#include "map.h"
#include "move.h"

class Run {
protected:
    int map_size_;
    int bots_amount_;
    int days_amount_;
    double progress;
    double progress_scale;
    const int bar_width = 70;
    const int damage_ = 20;
    Map today_map_;
    std::list<Bot> all_bots;

    void init(int map_size, int bots_amount, int days_amount);

public:
    Run() = default;

    void run(int map_size, int bots_amount, int days_amount);

    void print_progress(int today);
};
