#include "map.h"
#include "bot.h"

Map::Map(int size, int bots_amount, int food_amount)
    : map_(size, std::vector<Cell>(size))
    , size_(size)
    , bots_amount_(bots_amount)
    , food_amount_(food_amount) {
    spawn_bots(bots_amount_);
    respawn_food();    
}

void Map::spawn_bots(int bots_amount) {
    for (int i = 0; i < bots_amount; ++i) {
        map_[rand() % size_][rand() % size_].bots_.push_back(Bot(size_));
    }
}

void Map::respawn_food() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            map_[i][j].food_counter_ = 0;
        }
    }

    for (int i = 0; i < food_amount_; ++i) {
        ++map_[rand() % size_][rand() % size_].food_counter_;
    }
}

int Map::size() const {
    return size_;
}

int Map::bots_amount() const {
    return bots_amount_;
}

std::vector<Cell>& Map::operator[](const int i) {
    return map_[i];
}

Cell& Map::operator[](const Position& position) {
    return map_[position.x][position.y];
}

Map::Iterator::Iterator(Map& map, int row, int column)
    : map_(map)
    , iter_row_(row)
    , iter_column_(column) {}

Cell& Map::Iterator::operator*() {
    return map_[iter_row_][iter_column_];
}

Map::Iterator& Map::Iterator::operator++() {
    ++iter_column_;
    if (iter_column_ == map_.size_) {
        iter_column_ = 0;
        ++iter_row_;
    }
    return *this;
}

Map::Iterator Map::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool Map::Iterator::operator==(Iterator other) const {
    return iter_row_ == other.iter_row_ && iter_column_ == other.iter_column_;
}

bool Map::Iterator::operator!=(Iterator other) const {
    return !(*this == other);
}

Map::Iterator Map::begin() {
    return Iterator(*this);
}

Map::Iterator Map::end() {
    return Iterator(*this, size_, 0);
}
