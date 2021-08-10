#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <nlohmann/json.hpp>

#include "bot.h"
#include "file.h"
#include "map.h"
#include "move.h"
#include "parameters.h"

class Run {
protected:
    double progress;
    double progress_scale;
    const int bar_width = 70;
    Map map_;
    std::list<Bot> all_bots;
    File bots_amount_file_;
    File parameters_file_;

    void init();

public:
    Run() = default;

    void run();

    void print_progress(int today);

    void print_average();
};
