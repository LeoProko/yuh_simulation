#include "cell.h"

void Cell::reproduce(std::list<Bot>& bots) {
    if (bots_in_cell_.size() > 1) {
        std::sort(bots_in_cell_.rbegin(), bots_in_cell_.rend(), [](Bot* first, Bot* second) {
            return *first < *second;
        });
        Bot* mother = bots_in_cell_.front();
        Bot* father = *(++bots_in_cell_.begin());
        for (int i = 0; i < (mother->children_amount_ + father->children_amount_) / (2 * 10); ++i) {
            bots.emplace_back(mother, father);
        }
    }
}

void Cell::split_food() {
    for (auto& bot : bots_in_cell_) {
        double current_coef = bot->militancy_;
        if (total_coef_ != 0) {
            current_coef /= total_coef_;
        }
        bot->health_ = std::min(
            100,
            bot->health_ + static_cast<int>(current_coef * food_counter_ * 100.)
        );
    }
}

void Cell::altruists_activation() {
    for (const auto& bot : bots_in_cell_) {
        if (bot->is_altruist_) {
            for (auto& neighbour : bots_in_cell_) {
                if (neighbour->is_greenbeared_) {
                    neighbour->is_protected_ = true;
                }
            }
            return;
        }
    }
}

void Cell::enemy_activation() {
    for (auto& bot : bots_in_cell_) {
        if ((bot->is_altruist_ && parameters::random() % 2) || !bot->is_protected_) {
            bot->health_ = 0;
        }
        bot->is_protected_ = false;
    }
}

void Cell::do_all(std::list<Bot>& bots) {
    reproduce(bots);
    split_food();
    if (is_enemy_) {
        altruists_activation();
        enemy_activation();
    }
    bots_in_cell_.clear();
    total_coef_ = 0;
}

void Cell::clean() {
    bot_counter_ = 0;
}

void Cell::add_bot(Bot& bot) {
    bots_in_cell_.push_back(&bot);
    total_coef_ += bot.militancy_;
    ++bot_counter_;
}
