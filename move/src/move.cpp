#include "move.h"

void move(Bot& bot, Map& map, int damage) {
    std::vector<Position> positions;
    int left_border   = std::max(0,          bot.position_.x - 1);
    int right_border  = std::min(map.size(), bot.position_.x + 2);
    int top_border    = std::max(0,          bot.position_.y - 1);
    int bottom_border = std::min(map.size(), bot.position_.y + 2);

    for (int i = left_border; i < right_border; ++i) {
        for (int j = top_border; j < bottom_border; ++j) {
            positions.emplace_back(i, j);
        }     
    }

    std::sort(
        positions.begin(), 
        positions.end(), 
        [&] (const Position& first, const Position& second) {
            return map[first].food_counter_ < map[second].food_counter_;
        }
    );

    bot.health_ -= damage;
    bot.position_ = positions[bot.intelligence_ * positions.size() / 100];

    map[bot.position_].add_bot(bot);
}
