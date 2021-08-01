#pragma once

#include "bot.h"
#include "cell.h"
#include "position.h"

#include <vector>
#include <cstdlib>

class Map {
private:
    class Iterator {
    private:
        Map& map_;
        int iter_row_;
        int iter_column_;

    public:
        Iterator() = delete;

        Iterator(Map& map, int row = 0, int column = 0);

        Cell& operator*();

        Iterator& operator++();

        Iterator operator++(int);

        bool operator==(Iterator other) const;

        bool operator!=(Iterator other) const;
    };

    std::vector<std::vector<Cell>> map_;
    int size_;
    int bots_amount_;
    int food_amount_;

    void spawn_bots(std::deque<Bot>& all_bots);

    void respawn_food();

public:
    Map() = default;

    Map(std::deque<Bot>& all_bots, int size, int bots_amount = 0, int food_amount = 0);

    int size() const;

    int bots_amount() const;

    std::vector<Cell>& operator[](const int i);

    Cell& operator[](const Position& position);

    Iterator begin();

    Iterator end();
};
