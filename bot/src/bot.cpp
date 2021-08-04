#include "bot.h"
#include <iostream>

Bot::Bot(int map_size)
    : position_(Rand::random_() % map_size, Rand::random_() % map_size) {
    calibrate();
}

Bot::Bot(const Bot* mother, const Bot* father)
    : position_(mother->position_.x, mother->position_.y)
    , health_((mother->children_health_ + father->children_health_) / 2) {
    militancy_ = (mother->militancy_ + father->militancy_) / 2 + Rand::random_() % 4 - 2;
    attractiveness_ = (mother->attractiveness_ + father->attractiveness_) / 2 + Rand::random_() % 4 - 2;
    intelligence_ = (mother->intelligence_ + father->intelligence_) / 2 + Rand::random_() % 4 - 2;
    children_amount_ = (mother->children_amount_ + father->children_amount_) / 2 + Rand::random_() % 4 - 2;
    children_health_ = (mother->children_health_ + father->children_health_) / 2 + Rand::random_() % 4 - 2;
    calibrate();
}

void Bot::calibrate() {
//    double coefficient = 50. * genes_amount_ /
//                (militancy_ + intelligence_ + attractiveness_ +
//                 children_amount_ + children_health_);
    
    militancy_ = std::max(0, std::min(99, militancy_));
    attractiveness_ = std::max(0, std::min(99, attractiveness_));
    intelligence_ = std::max(0, std::min(99, intelligence_));
    children_amount_ = std::max(0, std::min(99, children_amount_));
    children_health_ = std::max(0, std::min(99, children_health_));
}

bool operator<(const Bot& first, const Bot& second) {
    return first.attractiveness_ < second.attractiveness_;
}
