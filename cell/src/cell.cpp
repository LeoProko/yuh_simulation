#include "cell.h"

void Cell::do_all(std::list<Bot>& all_bots) {
    reproduce(all_bots);
    split_food();    
}

void Cell::reproduce(std::list<Bot>& all_bots) {
    if (bots_.size() > 1) {
        std::sort(bots_.rbegin(), bots_.rend());
        Bot* mother = bots_.front();
        Bot* father = *(++bots_.begin());
        for (int i = 0; i < (mother->childern_amount_ + father->childern_amount_) / 2; ++i) {
            all_bots.emplace_back(mother, father);
        }
    }
}

void Cell::split_food() {
    for (auto& bot : bots_) {
        int current_coef = bot->militancy_ * 0.6 + bot->health_ * 0.4;
        if (total_coef_ != 0) {
            current_coef /= total_coef_;
        }
        bot->health_ = std::min(100, bot->health_ + current_coef);
    }
}

void Cell::add_bot(Bot& bot) {
    bots_.push_back(&bot);
    total_coef_ += bot.militancy_ * 0.6 + bot.health_ * 0.4;
    ++bot_counter_;
}
