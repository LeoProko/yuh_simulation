#pragma once

#include "bot.h"
#include "cell.h"
#include "parameters.h"
#include "position.h"
#include <atomic>

#include <iostream>
#include <list>
#include <thread>
#include <vector>

class Map {
private:
    std::vector<std::vector<Cell>> map_;

public:
    int food_amount_ = 0;

    Map();

    void clean_and_respawn(int thread_num);

    std::vector<Cell>& operator[](const int i);

    const std::vector<Cell>& operator[](const int i) const;

    Cell& operator[](const Position& position);
};
