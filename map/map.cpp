#include "map.h"

class Map {
private:
    std::vector<std::vector<Point>> map_;
    size_t size_;
    size_t bots_amount_;
    size_t food_amount_;

public:
    Map(size_t size, size_t bots_amount, size_t food_amount) :
        size_(size),
        bots_amount_(bots_amount),
        food_amount_(food_amount) {
        
    }
};