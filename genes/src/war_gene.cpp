#include "../include/war_gene.h"

class WarGene {
private:
    std::vector<std::vector<Cell>>& map_;
    Position& position_;

public:
    WarGene(std::vector<std::vector<Cell>>& map, Position& position)
        : map_(map)
        , position_(position) {}

    int probability;

    void action() {
        if (map_[position_.x][position_.y].bot_counter > 1) {
            //do something
        }
    }
};
