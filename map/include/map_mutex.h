#pragma once

#include "cell_mutex.h"
#include "position.h"

#include <vector>
#include <cstdlib>

class Map_mutex {
private:
    std::vector<std::vector<Cell_mutex>> map_;
    int size_;
    int bots_amount_;
    int food_amount_;

public:
    Map_mutex(int size, int bots_amount, int food_amount);

    void RespawnFood();

    std::vector<Cell_mutex>& operator[](const int i);
};
