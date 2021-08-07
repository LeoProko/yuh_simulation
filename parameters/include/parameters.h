#pragma once

#include <iostream>
#include <random>

namespace parameters {
    extern std::mt19937 random_;
    extern int map_size;
    extern int bots_amount;
    extern int altruists_amount;
    extern int days_amount;
    extern int food_amount;
    extern int food_per_cell;
    extern int enemies_amount;
    extern int damage;
    extern int mutation;
    extern int move_error;

    int random();

    void print();
}
