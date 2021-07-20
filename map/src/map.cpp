#include "../include/map.h"

class Map {
private:
    std::vector<std::vector<Cell>> map_;
    size_t size_;
    size_t bots_amount_;
    size_t food_amount_;

public:
    Map(size_t size, size_t bots_amount, size_t food_amount)
        : size_(size)
        , bots_amount_(bots_amount)
        , food_amount_(food_amount) {
        RespawnFood();    
    }

    void RespawnFood() {
        for (size_t i = 0; i < size_; ++i) {
            for (size_t j = 0; j < size_; ++j) {
                map_[i][j].food_count_ = 0;
            }
        }

        std::random_device rd;
        for (size_t i = 0; i < food_amount_; ++i) {
            ++map_[rd()][rd()].food_count_;
        }
    }
};