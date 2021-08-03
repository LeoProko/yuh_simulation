#include "bot.h"
#include <iostream>

Bot::Bot(int map_size, std::mt19937& random)
    : position_(random() % map_size, random() % map_size) {
//    calibrate();
}

Bot::Bot(const Bot* mother, const Bot* father)
    : position_(mother->position_.x, mother->position_.y)
    , health_((mother->children_health_ + father->children_health_) / 2) {
    militancy_ = (mother->militancy_ + father->militancy_) / 2;
    attractiveness_ = (mother->attractiveness_ + father->attractiveness_) / 2;
    intelligence_ = (mother->intelligence_ + father->intelligence_) / 2;
    children_amount_ = (mother->children_amount_ + father->children_amount_) / 2;
    children_health_ = (mother->children_health_ + father->children_health_) / 2;
//    calibrate();
}

void Bot::calibrate() {
    double coefficient = 50. * genes_amount_ /
                (militancy_ + intelligence_ + attractiveness_ +
                 children_amount_ + children_health_);
    for (int i = 0; i < genes_amount_; ++i) {
        *genes_iter_[i] *= coefficient;
        *genes_iter_[i] = std::min(std::max(*genes_iter_[i], 0), 99);
    }
}

bool operator<(const Bot& first, const Bot& second) {
    return first.attractiveness_ < second.attractiveness_;
}
