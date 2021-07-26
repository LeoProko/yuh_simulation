#include "behavior.h"
#include "bot.h"

Behavior::Behavior(Map* today_map, Map* tomorrow_map) {
    today_map_ = today_map;
    tomorrpow_map_ = tomorrow_map;
}

void Behavior::action(const Bot&) {}

std::vector<std::unique_ptr<Behavior>> Behavior::get_behaviors() const {
    std::vector<std::unique_ptr<Behavior>> behaviors;
    behaviors.emplace_back(new Fight);
    return behaviors;
}


void Fight::action(const Bot& bot) {
    if (rand() % 100 < bot.militancy_) {
        if ((*tomorrpow_map_)[bot.position_.x][bot.position_.y].bot_counter_ >= 2) {
            // do something
        }
    }
}
