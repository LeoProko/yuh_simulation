#pragma once

#include "bot.h"
#include "mpmc_queue.h"

struct Cell_lock_free {
    int bot_counter_ = 0;
    int food_counter_ = 0;

    MPMCQueue<Bot*>* queue = nullptr;

    Cell_lock_free() {
        queue = new MPMCQueue<Bot*>;
    }

    Cell_lock_free(const Cell_lock_free& other_cell):
            bot_counter_(other_cell.bot_counter_),
            food_counter_(other_cell.food_counter_)
    {
        queue = new MPMCQueue<Bot*>;
    }
};
