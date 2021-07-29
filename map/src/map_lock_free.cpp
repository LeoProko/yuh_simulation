#include "map_lock_free.h"

Map_lock_free::Map_lock_free(int size, int bots_amount, int food_amount)
        : map_(size, std::vector<Cell_lock_free>(size))
        , size_(size)
        , bots_amount_(bots_amount)
        , food_amount_(food_amount) {
    RespawnFood();
}

void Map_lock_free::RespawnFood() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            map_[i][j].food_counter_ = 0;
        }
    }

    for (int i = 0; i < food_amount_; ++i) {
        ++map_[rand() % size_][rand() % size_].food_counter_;
    }
}

std::vector<Cell_lock_free>& Map_lock_free::operator[](const int i) {
    return map_[i];
}

