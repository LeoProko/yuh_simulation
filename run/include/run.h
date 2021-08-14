#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <nlohmann/json.hpp>

#include "bot.h"
#include "file.h"
#include "map.h"
#include "move.h"
#include "parameters.h"

class Run {
protected:
    int bots_amount_;
    double progress_;
    double progress_scale_;
    const int bar_width_ = 70;
    Map map_;
    std::vector<std::list<Bot>> all_bots_;
    std::vector<std::thread> threads_;
    File bots_amount_file_;
    File parameters_file_;

    void init();

public:
    Run() = default;

    void thread_move(int thread_num);

    void thread_do_all(int thread_num, std::list<Bot>& bots);

    void thread_bot_erase(int thread_num);

    void add_bots(std::list<Bot>& bots);

    void update_bots_amount();

    void print_progress(int today);

    void print_average();

    void run();
};
