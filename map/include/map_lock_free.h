#pragma once

#include "cell_lock_free.h"
#include "position.h"

#include <vector>
#include <cstdlib>

class Map_lock_free {
private:
    std::vector<std::vector<Cell_lock_free>> map_;
    int size_;
    int bots_amount_;
    int food_amount_;

public:
    Map_lock_free(int size, int bots_amount, int food_amount);

    void RespawnFood();

    std::vector<Cell_lock_free>& operator[](const int i);
};
