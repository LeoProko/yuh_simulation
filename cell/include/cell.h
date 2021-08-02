#pragma once

#include <deque>

#include "bot.h"
#include "position.h"

class Cell {
private:
    void reproduce();

    void split_food();

public:
    int bot_counter_ = 0;
    int food_counter_ = 0;

    // в эту переменную при перемещении бота в нашу клетку в функции move нужно делать
    // total_health += (bot.militancy_ * 0.6 + bot.health_ * 0.4),
    // чтобы не проходиться отдельно в функции Cell::split_food,
    // а под конец дня снова очищать эту переменную
    int total_health = 0;

    std::deque<Bot*> bots_;

    Cell() = default;

    void do_all();
};
