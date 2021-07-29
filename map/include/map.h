#pragma once

#include "bot.h"
#include "cell.h"
#include "position.h"

#include <vector>
#include <cstdlib>

class Map {
public:
    std::vector<std::vector<Cell>> map_;
    int size_;
    int bots_amount_;
    int food_amount_;

public:
    Map() = default;

    Map(int size, int bots_amount = 0, int food_amount = 0);

    void RespawnFood();

    std::vector<Cell>& operator[](const int i);
};
