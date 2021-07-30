#include "move.h"

void move(Bot& bot, Map& map) {
    if (rand() < bot.intelligence_) {
        std::vector<Position> best_positions;
        int max_food = 0;
        int left_border   = std::max(0,          bot.position_.x - 1);
        int right_border  = std::min(map.size(), bot.position_.x + 2);
        int top_border    = std::max(0,          bot.position_.y - 1);
        int bottom_border = std::min(map.size(), bot.position_.y + 2);

        for (int i = left_border; i < right_border; ++i) {
            for (int j = top_border; j < bottom_border; ++i) {
                if (map[i][j].food_counter_ > max_food) {
                    max_food = map[i][j].food_counter_;
                    best_positions.clear();
                    best_positions.emplace_back(i, j);
                } else if (map[i][j].food_counter_ == max_food) {
                    max_food = map[i][j].food_counter_;
                    best_positions.emplace_back(i, j);
                }
            }     
        }

        bot.position_ = best_positions[rand() % best_positions.size()];
    } else {
        bot.position_.x += rand() % 3 - 1;
        bot.position_.y += rand() % 3 - 1;
    }
}
