#pragma once

#include "bot.h"
#include <vector>
#include <mutex>

struct Cell_mutex {
    int bot_counter_ = 0;
    int food_counter_ = 0;

    std::vector<Bot*> queue;
    std::mutex* mutex = nullptr;

    Cell_mutex() {
        mutex = new std::mutex;
    }

    Cell_mutex(const Cell_mutex& other_cell):
    bot_counter_(other_cell.bot_counter_),
    food_counter_(other_cell.food_counter_)
    {
        mutex = new std::mutex;
    }
};
