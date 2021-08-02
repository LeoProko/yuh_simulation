#include "cell.h"

void Cell::do_all() {
    reproduce();
    split_food();    
}

void Cell::reproduce() {
    if (bots_.size() > 1) {
        std::sort(bots_.begin(), bots_.end(), [](Bot b1, Bot b2) { return b2 < b1; });
        
        Bot* mother = *bots_.begin();
        Bot* father = *(++bots_.begin());
        for (int i = 0; i < (mother->childern_amount_ + father->childern_amount_) / 2; ++i) {
            // run->all_bots.emplace_back(mother, father);
        }
    }
}

void Cell::split_food() {
    for (auto& b : bots_) {
        int tmp = b->militancy_ * 0.6 + b->health_ * 0.4;
        b->health_ = std::min(100, b->health_ + tmp / total_health);
    }
}
