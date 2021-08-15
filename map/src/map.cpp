#include "map.h"

Map::Map()
    : map_(parameters::map_size, std::vector<Cell>(parameters::map_size)) {
    respawn_food();
}

std::vector<Cell>& Map::operator[](const int i) {
    return map_[i];
}

const std::vector<Cell>& Map::operator[](const int i) const {
    return map_[i];
}

Cell& Map::operator[](const Position& position) {
    return map_[position.x][position.y];
}

void Map::spawn_bots(std::list<Bot>& all_bots) {
    for (int i = 0; i < parameters::bots_amount; ++i) {
        all_bots.emplace_back();
        (*this)[all_bots.back().position_].add_bot(all_bots.back());
    }
}

void Map::respawn_food() {
    for (int i = 0; i < parameters::food_amount; ++i) {
        int added_food = parameters::random() % (parameters::food_per_cell + 1);
        food_amount_ += added_food;
        map_[parameters::random() % parameters::map_size]
        [parameters::random() % parameters::map_size].food_counter_ = added_food;
    }
}

void Map::clean() {
    for (int i = 0; i < parameters::map_size; ++i) {
        for (int j = 0; j < parameters::map_size; ++j) {
            map_[i][j].food_counter_ = 0;
            map_[i][j].is_enemy_ = false;
            map_[i][j].bot_counter_ = 0;
        }
    }
}

void Map::respawn_enemies() {
    for (int i = 0; i < parameters::enemies_amount; ++i) {
        map_[parameters::random() % parameters::map_size]
        [parameters::random() % parameters::map_size].is_enemy_ = true;
    }
}


void Map::clean_and_respawn(int thread_num) {
    int thread_block_size = parameters::map_size /
                            parameters::threads_amount;
    int thread_block_size_reminder = parameters::map_size %
                                     parameters::threads_amount;
    int from = thread_num * thread_block_size;
    int to = (1 + thread_num) * thread_block_size +
             (thread_num == (parameters::threads_amount - 1)) *
             thread_block_size_reminder;
    int thread_food_cnt = 0;
    for (int i = from; i < to; ++i) {
        for (int j = 0; j < parameters::map_size; ++j) {
            int added_food = parameters::random() %
                             (parameters::map_size * parameters::map_size) <
                             parameters::food_amount;
            thread_food_cnt += added_food;
            map_[i][j].food_counter_ = added_food;
            map_[i][j].is_enemy_ = parameters::random() %
                                   (parameters::map_size * parameters::map_size) <
                                   parameters::enemies_amount;
            map_[i][j].bot_counter_ = 0;
        }
    }
    parameters::mutex.lock();
    food_amount_ += thread_food_cnt;
    parameters::mutex.unlock();
}
