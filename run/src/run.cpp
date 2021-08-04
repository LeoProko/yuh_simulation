#include "run.h"

void Run::init(int map_size, int bots_amount, int days_amount) {
    std::cout << "INITIALIZATION BEGIN\n";
    map_size_ = map_size;
    bots_amount_ = bots_amount;
    days_amount_ = days_amount;
    progress = 0.;
    progress_scale = 1. / days_amount_;
    today_map_ = Map(map_size_, bots_amount_, bots_amount_);
    for (int i = 0; i < bots_amount_; ++i) {
        all_bots.emplace_back(map_size_);
    }
    std::cout << "INITIALIZATION COMPLETED\n";
}

void Run::print_progress(int today) {
    if (progress - 0. >= 1e-6) {
        std::cout << "\033[F\r";
        std::cout.flush();
        std::cout << "\033[F\r";
        std::cout.flush();
        std::cout << "\033[F\r";
        std::cout.flush();
    }
    progress += progress_scale;
    std::cout << "[";
    int position = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < position) {
            std::cout << "=";
        }
        else if (i == position) {
            std::cout << ">";
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << "] " << static_cast<int>(progress * 100.0) << "%\n";
    std::cout << "Day number " << today << "\n";
    std::cout << "Number of bots today: " << all_bots.size() << "\n";
}

void Run::run(int map_size, int bots_amount, int days_amount) {
    std::cout << "START SIMULATION WITH PARAMETERS:\n";
    std::cout << "map_size = " << map_size << "\n";
    std::cout << "bots_amount = " << bots_amount << "\n";
    std::cout << "days_amount = " << days_amount << "\n";

    init(map_size, bots_amount, days_amount);
    int64_t passes_amount = 0;

    for (int today = 1; today <= days_amount_; ++today) {
        print_progress(today);
        for (auto bot_iter = all_bots.begin(); bot_iter != all_bots.end();) {
            if (bot_iter->health_ > damage_) {
                move(*bot_iter, today_map_, damage_);
                ++bot_iter;
            } else {
                auto bot_iter_to_erase = bot_iter++;
                all_bots.erase(bot_iter_to_erase);
            }
        }
        std::list<Bot> new_bots;
        for (auto& bot : all_bots) {
            today_map_[bot.position_].do_all(new_bots);
            ++passes_amount;
        }
        for (const auto& new_bot : new_bots) {
            all_bots.push_back(new_bot);
        }
        today_map_.respawn_food();
        if (all_bots.size() == 0) {
            break;
        }
    }
    if (all_bots.size() == 0) {
        std::cout << "SIMULATION FAILED. ALL BOTS DEAD\n";
    }
    std::cout << "Passes amount = " << passes_amount << "\n";
}
