#include "move.h"

void move(Bot& bot, Map& map) {
    int bots_range = bot.vision_ / 10;
    std::vector<Position> positions;
    int left_border   = std::max(0,                    bot.position_.x - bots_range    );
    int right_border  = std::min(parameters::map_size, bot.position_.x + bots_range + 1);
    int bottom_border = std::max(0,                    bot.position_.y - bots_range    );
    int top_border    = std::min(parameters::map_size, bot.position_.y + bots_range + 1);

    for (int x = left_border; x < right_border; ++x) {
        for (int y = bottom_border; y < top_border; ++y) {
            positions.emplace_back(x, y);
        }     
    }

    std::sort(
        positions.begin(),
        positions.end(),
        [&] (const Position& first, const Position& second) {
            return map[first].food_counter_ < map[second].food_counter_;
        }
    );

    Position prev_position = bot.position_;

    if (positions.size() > 1) {
        bot.position_ = positions[
            std::min(
                static_cast<int>(positions.size()) - 1,
                std::max(
                    0,
                    static_cast<int>(
                        bot.intelligence_ * positions.size() / 100 +
                        parameters::random() % (
                            std::max(
                                1,
                                static_cast<int>(parameters::move_error * positions.size() / 100)
                            )
                        ) -
                        (parameters::move_error * positions.size() / 200)
                    )
                )
            )
        ];
    }

    int path_length = std::sqrt(
        (bot.position_.x - prev_position.x) * 
        (bot.position_.x - prev_position.x) +
        (bot.position_.y - prev_position.y) * 
        (bot.position_.y - prev_position.y)
    );

    ++bot.lifetime_;
    bot.health_ -= parameters::damage * std::max(1, path_length + bot.lifetime_ / 10);

    map[bot.position_].add_bot(bot);
}
