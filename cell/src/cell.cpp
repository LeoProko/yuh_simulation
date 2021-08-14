#include "cell.h"

void Cell::reproduce(std::list<Bot>& bots) {
    if (bots_in_cell_.size() > 1) {
        std::sort(
            bots_in_cell_.rbegin(),
            bots_in_cell_.rend(),
            [](Bot* first, Bot* second) {
                return *first < *second;
            }
        );
        Bot* mother = bots_in_cell_.front();
        Bot* father = *(++bots_in_cell_.begin());
        parameters::reproduce_mutex.lock();
        for (int i = 0; i < (mother->children_amount_ + father->children_amount_) / (2 * 10); ++i) {
            bots.emplace_back(mother, father);
        }
        parameters::reproduce_mutex.unlock();
        mother->health_ -= parameters::damage *
            mother->children_amount_ / 10;
        father->health_ -= parameters::damage *
            father->children_amount_ / 10;
    }
}

void Cell::split_food() {
    for (auto& bot : bots_in_cell_) {
        double current_collect_coeff = bot->collect_;
        if (total_collect_coeff_ != 0) {
            current_collect_coeff /= total_collect_coeff_;
        }
        bot->health_ = std::max(0, std::min(
            100'000,
            bot->health_ + static_cast<int>(current_collect_coeff * food_counter_ * 100.)
        ));
    }
}

void Cell::share_food() {
    std::sort(
        bots_in_cell_.begin(),
        bots_in_cell_.end(),
        [](Bot* first, Bot* second) {
            return first->health_ > second->health_;
        }
    );
    for (
        int front = 0, back = bots_in_cell_.size() - 1;
        front < back;
        ++front, --back) {
        int food_to_share = bots_in_cell_[front]->share_;
        bots_in_cell_[front]->health_ -= food_to_share;
        bots_in_cell_[back]->health_ += food_to_share;
    }
}

void Cell::fight() {
    std::sort(
        bots_in_cell_.begin(),
        bots_in_cell_.end(),
        [](Bot* first, Bot* second) {
            return first->militancy_ > second->militancy_;
        }
    );
    for (
        int first = 0, second = 1;
        second < static_cast<int>(bots_in_cell_.size());
        first += 2, second += 2) {
        int food_to_share = 0;
        if (bots_in_cell_[first]->militancy_ > bots_in_cell_[second]->militancy_) {
            food_to_share -= parameters::damage;
        } else if (bots_in_cell_[first]->militancy_ < bots_in_cell_[second]->militancy_) {
            food_to_share += parameters::damage;
        }
        bots_in_cell_[first]->health_ -= food_to_share;
        bots_in_cell_[second]->health_ += food_to_share;
    }
}

void Cell::do_all(std::list<Bot>& bots) {
    if (!bots_in_cell_.empty()) {
        if (is_enemy_) {
            altruists_activation();
            enemy_activation();
        }
        split_food();
        share_food();
        fight();
        reproduce(bots);
        bots_in_cell_.clear();
        total_collect_coeff_ = 0;
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
            bot->health_ = parameters::damage;
        }
        bot->is_protected_ = false;
    }
}

void Cell::add_bot(Bot& bot) {
    std::unique_lock<std::mutex> uniq_lock(*move_mutex);
    bots_in_cell_.push_back(&bot);
    total_collect_coeff_ += bot.collect_;
    ++bot_counter_;
}

Cell::Cell(const Cell&) {
    move_mutex = new std::mutex;
}

Cell::~Cell() {
    delete move_mutex;
}
