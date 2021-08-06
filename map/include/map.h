#pragma once

#include "bot.h"
#include "cell.h"
#include "parameters.h"
#include "position.h"

#include <iostream>
#include <list>
#include <vector>

class Map {
private:
    std::vector<std::vector<Cell>> map_;
    int food_amount_ = 0;

    void spawn_bots(std::list<Bot>& all_bots);

    void clean();

    void respawn_food();

    void respawn_enemies();

public:
    Map();

    void clean_and_respawn();

    std::vector<Cell>& operator[](const int i);

    Cell& operator[](const Position& position);

};
