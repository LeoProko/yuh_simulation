#include "fight.h"

void Fight::action(const Bot& bot, Map& map) {
    if (rand() % 100 < bot.militancy_) {
        if (map[bot.position_.x][bot.position_.y].bot_counter_ >= 2) {
            // do something
        }
    }
}
