#include "cell.h"

void Cell::do_all(std::list<Bot>& all_bots) {
    reproduce(all_bots);
    split_food();
    bots_.clear();
    bot_counter_ = 0;
    total_coef_ = 0;
}

void Cell::reproduce(std::list<Bot>& all_bots) {
    if (bots_.size() > 1) {
        std::sort(bots_.rbegin(), bots_.rend());
        Bot* mother = bots_.front();
        Bot* father = *(++bots_.begin());
        for (int i = 0; i < (mother->children_amount_ + father->children_amount_) / 2; ++i) {
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
        bot->health_ = std::min(100, bot->health_ + current_coef * food_counter_);
    }
}

void Cell::add_bot(Bot& bot) {
    bots_.push_back(&bot);
    total_coef_ += bot.militancy_ * 0.6 + bot.health_ * 0.4;
    ++bot_counter_;
}
