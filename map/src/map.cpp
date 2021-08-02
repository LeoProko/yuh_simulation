#include "map.h"
#include "bot.h"

Map::Map(std::list<Bot>& all_bots, int size, int bots_amount, int food_iter)
    : map_(size, std::vector<Cell>(size))
    , size_(size)
    , bots_amount_(bots_amount)
    , food_iter_(food_iter) {
    spawn_bots(all_bots);
    respawn_food();    
}

std::vector<Cell>& Map::operator[](const int i) {
    return map_[i];
}

Cell& Map::operator[](const Position& position) {
    return map_[position.x][position.y];
}

void Map::spawn_bots(std::list<Bot>& all_bots) {
    for (int i = 0; i < bots_amount_; ++i) {
        all_bots.push_back(Bot(size_));
        (*this)[all_bots.back().position_].bots_.push_back(&all_bots.back());
    }
}

void Map::respawn_food() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            map_[i][j].food_counter_ = 0;
        }
    }

    for (int i = 0; i < food_iter_; ++i) {
        int added_food = std::rand() % 10;
        food_amount_ += added_food;
        map_[rand() % size_][rand() % size_].food_counter_ = added_food;
    }
}

int Map::size() const {
    return size_;
}

int Map::bots_amount() const {
    return bots_amount_;
}
