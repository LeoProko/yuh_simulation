#include "map.h"

Map::Map(int size, int bots_amount, int food_amount)
    : map_(size, std::vector<Cell>(size))
    , size_(size)
    , bots_amount_(bots_amount)
    , food_amount_(food_amount) {
    RespawnFood();    
}

void Map::RespawnFood() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            map_[i][j].food_counter_ = 0;
        }
    }

    for (int i = 0; i < food_amount_; ++i) {
        ++map_[rand()][rand()].food_counter_;
    }
}

std::vector<Cell>& Map::operator[](const int i) {
    return map_[i];
}
