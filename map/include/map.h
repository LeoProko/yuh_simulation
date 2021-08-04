#pragma once

#include "bot.h"
#include "cell.h"
#include "position.h"
#include "rand.h"

#include <iostream>
#include <list>
#include <vector>

class Map {
private:
    std::vector<std::vector<Cell>> map_;
    int size_;
    int bots_amount_;
    int food_iter_;
    int food_amount_ = 0;

    void spawn_bots(std::list<Bot>& all_bots);

public:
    Map() = default;

    Map(
        int size,
        int bots_amount = 0,
        int food_iter = 0
    );

    void respawn_food();

    int size() const;

    int bots_amount() const;

    std::vector<Cell>& operator[](const int i);

    Cell& operator[](const Position& position);

};
