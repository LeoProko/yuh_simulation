#include "move.h"

void move(Bot& bot, Map& map) {
    int bots_range = 1 + bot.vision_ / 10;
    std::vector<Position> positions;
    int left_border   = std::max(0,                    bot.position_.x - bots_range);
    int right_border  = std::min(parameters::map_size, bot.position_.x + bots_range + 1);
    int top_border    = std::max(0,                    bot.position_.y - bots_range);
    int bottom_border = std::min(parameters::map_size, bot.position_.y + bots_range + 1);

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

    Position old_position = bot.position_;
    //bot.position_ = positions[bot.intelligence_ * positions.size() / 100];
    //bot.position_ = positions[Rand::random() % positions.size()];
    bot.position_ = positions[
        std::min(
            static_cast<int>(positions.size()) - 1,
            std::max(
                0,
                static_cast<int>(
                    bot.intelligence_ * positions.size() / 100 +
                    (parameters::random() % static_cast<int>(parameters::move_error * positions.size() / 100))  -
                    (parameters::move_error * positions.size()) / 200
                )
            )
        )
    ];

    int path_length = static_cast<int>(
        sqrt(
            (bot.position_.x - old_position.x) * 
            (bot.position_.x - old_position.x) +
            (bot.position_.y - old_position.y) * 
            (bot.position_.y - old_position.y)
        )
    );

    ++bot.lifetime_;
    bot.health_ -= parameters::damage * path_length;

    map[bot.position_].add_bot(bot);
}
