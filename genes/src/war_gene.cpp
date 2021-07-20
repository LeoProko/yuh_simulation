#include "war_gene.h"

class WarGene {
private:
    Map& map_;
    Position& position_;

public:
    WarGene(Map& map, Position& position)
        : map_(map)
        , position_(position) {}

    int probability;

    void action() {
        if (map_[position_.x][position_.y].bot_counter_ > 1) {
            //do something
        }
    }
};
