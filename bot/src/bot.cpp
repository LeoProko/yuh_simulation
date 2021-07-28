#include "bot.h"

Bot::Bot(int map_size)
    : position_(rand() % map_size, rand() % map_size)
    , health_(100)
    , food_amount_(1)
    , militancy_(rand() % 101)
    , intelligence_(rand() % 101)
    , attractiveness_(rand() % 101) {
    float coeff = 150./(militancy_ + intelligence_ + attractiveness_);
    militancy_ *= coeff;
    intelligence_ *= coeff;
    attractiveness_ *= coeff;
}

Bot::Bot(Bot& mother, Bot& father) 
    : position_(mother.position_.x, mother.position_.y)
    , health_(100)
    , food_amount_(1) {
    militancy_ = std::min(100, std::max(0, (mother.militancy_ + father.militancy_) / 2 + rand() % 4 - 2));
    attractiveness_ = std::min(100, std::max(0, (mother.attractiveness_ + father.attractiveness_) / 2 + rand() % 4 - 2));
    intelligence_ = std::min(100, std::max(0, (mother.intelligence_ + father.intelligence_) / 2 + rand() % 4 - 2));
}
