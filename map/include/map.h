#include "cell.h"
#include "position.h"

#include <vector>
#include <random>

class Map {
private:
    std::vector<std::vector<Cell>> map_;
    int size_;
    int bots_amount_;
    int food_amount_;

public:
    Map(int size, int bots_amount, int food_amount);

    void RespawnFood();

    std::vector<Cell>& operator[](const int i);
};
