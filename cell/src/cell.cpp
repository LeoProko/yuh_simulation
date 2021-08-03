#include "cell.h"

void Cell::do_all() {
    reproduce();
    split_food();    
}

void Cell::reproduce() {
    if (bots_.size() > 1) {
        std::sort(bots_.begin(), bots_.end(), [](const Bot& b1, const Bot& b2) { return b2 < b1; });
        
        Bot* mother = *bots_.begin();
        Bot* father = *(++bots_.begin());
        for (int i = 0; i < (mother->childern_amount_ + father->childern_amount_) / 2; ++i) {
            // run->all_bots.emplace_back(mother, father);
        }
    }
}

void Cell::split_food() {
    for (auto& bot : bots_) {
        int current_coef = bot->militancy_ * 0.6 + bot->health_ * 0.4;
        bot->health_ = std::min(100, bot->health_ + current_coef / total_coef_);
    }
}

void Cell::add_bot(Bot& bot) {
    bots_.push_back(&bot);
    total_coef_ += bot.militancy_ * 0.6 + bot.health_ * 0.4;
    ++bot_counter_;
}
