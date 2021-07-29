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

    void spawn_bots(int bot_count);

public:
    Map() = default;

    Map(int size, int bots_amount = 0, int food_amount = 0);

    void respawn_food();

    int size() const;

    int bots_amount() const;

    std::vector<Cell>& operator[](const int i);

    Iterator begin();

    Iterator end();
};
