#pragma once

#include <iostream>
#include <list>
#include <vector>

#include "bot.h"
#include "map.h"
#include "move.h"
#include "parameters.h"

class Run {
protected:
    double progress;
    double progress_scale;
    const int bar_width = 70;
    Map today_map_;
    std::list<Bot> all_bots;

    void init();

public:
    Run() = default;

    void run();

    void print_progress(int today);

    void print_average() const;
};
