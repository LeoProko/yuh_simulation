#include "map.h"

Map::Map()
    : map_(parameters::map_size, std::vector<Cell>(parameters::map_size)) {
    std::vector<std::thread> threads(parameters::threads_amount);
    for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
        threads[thread_num] = std::thread(&Map::clean_and_respawn, this, thread_num);
    }
    for (auto& thread : threads) {
        thread.join();
    }
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

void Map::clean_and_respawn(int thread_num) {
    int thread_block_size = parameters::map_size /
                            parameters::threads_amount;
    int thread_block_size_reminder = parameters::map_size %
                                     parameters::threads_amount;
    int from = thread_num * thread_block_size;
    int to = (1 + thread_num) * thread_block_size +
             (thread_num == (parameters::threads_amount - 1)) *
             thread_block_size_reminder;
    int thread_food_amount = 0;
    for (int y = from; y < to; ++y) {
        for (int x = 0; x < parameters::map_size; ++x) {
            int added_food = parameters::random() %
                             (parameters::map_size * parameters::map_size) <
                             parameters::food_amount;
            added_food *= parameters::random() % parameters::food_per_cell;
            thread_food_amount += added_food;
            map_[y][x].food_counter_ = added_food;
            map_[y][x].is_enemy_ = parameters::random() %
                                   (parameters::map_size * parameters::map_size) <
                                   parameters::enemies_amount;
            map_[y][x].bot_counter_ = 0;
        }
    }
    parameters::mutex.lock();
    food_amount_ += thread_food_amount;
    parameters::mutex.unlock();
}
