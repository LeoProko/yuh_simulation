#pragma once

#include "behaviors.h"

class Cell {
    int bot_counter_ = 0;
    int food_counter_ = 0;

    Cell() = default;

    void do_all();
};
