#include "bot.h"

Bot::Bot(int map_size)
    : position_(std::rand() % map_size, std::rand() % map_size)
    , health_(std::rand() % 101)
    , food_amount_(5 + std::rand() % 5)
    , militancy_(std::rand() % 101)
    , intelligence_(std::rand() % 101)
    , attractiveness_(std::rand() % 101)
    , childern_amount_(std::rand() % 101)
    , children_health_(std::rand() % 101) {
    calibrate();
}

Bot::Bot(const Bot& mother, const Bot& father) 
    : position_(mother.position_.x, mother.position_.y)
    , health_((mother.health_ + father.health_) / 2)
    , food_amount_(5 + std::rand() % 5)
    , militancy_(std::min(100, std::max(0, (mother.militancy_ + father.militancy_) / 2 + std::rand() % 4 - 2)))
    , attractiveness_(std::min(100, std::max(0, (mother.attractiveness_ + father.attractiveness_) / 2 + std::rand() % 4 - 2)))
    , intelligence_(std::min(100, std::max(0, (mother.intelligence_ + father.intelligence_) / 2 + std::rand() % 4 - 2)))
    , childern_amount_(std::min(100, std::max(0, (mother.childern_amount_ + father.childern_amount_) / 2 + std::rand() % 4 - 2)))
    , children_health_(std::min(100, std::max(0, (mother.children_health_ + father.children_health_) / 2 + std::rand() % 4 - 2))) {
    calibrate();
}

void Bot::calibrate() {
    float coeff = 50. * genes_amount_ / (militancy_ + intelligence_ + attractiveness_ + childern_amount_ + children_health_);
    militancy_ *= coeff;
    intelligence_ *= coeff;
    attractiveness_ *= coeff;
    childern_amount_ *= coeff;
    children_health_ *= coeff;
}