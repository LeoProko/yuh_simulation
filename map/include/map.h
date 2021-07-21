#include "cell.h"
#include "position.h"

#include <vector>
#include <random>

class Map {
private:
    std::vector<std::vector<Cell>> map_;
    size_t size_;
    size_t bots_amount_;
    size_t food_amount_;

public:
    Map(size_t size, size_t bots_amount, size_t food_amount);

    void RespawnFood();

    std::vector<Cell>& operator[](const size_t i);
};
