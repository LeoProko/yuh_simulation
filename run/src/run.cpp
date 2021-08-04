#include "run.h"

void Run::init(int map_size, int bots_amount, int days_amount, int food_amount) {
    std::cout << "INITIALIZATION BEGIN\n";
    map_size_ = map_size;
    bots_amount_ = bots_amount;
    days_amount_ = days_amount;
    progress = 0.;
    progress_scale = 1. / days_amount_;
    today_map_ = Map(map_size_, bots_amount_, food_amount);
    for (int i = 0; i < bots_amount_; ++i) {
        all_bots.emplace_back(map_size_);
    }
    std::cout << "INITIALIZATION COMPLETED\n";
}

void Run::print_average() const {
    int avg_militancy = 0;
    int avg_intelligence = 0;
    int avg_children_amount = 0;
    int avg_children_health = 0;
    int avg_health = 0;
    int avg_lifetime = 0;
    for (auto& bot : all_bots) {
        avg_militancy += bot.militancy_;
        avg_intelligence += bot.intelligence_;
        avg_children_amount += bot.children_amount_;
        avg_children_health += bot.children_health_;
        avg_health += bot.health_;
        avg_lifetime += bot.lifetime_;
    }
    avg_militancy /= all_bots.size();
    avg_intelligence /= all_bots.size();
    avg_children_amount /= all_bots.size();
    avg_children_health /= all_bots.size();
    avg_health /= all_bots.size();
    avg_lifetime /= all_bots.size();
    std::cout << "average militancy: " << avg_militancy << " \n";
    std::cout << "average intelligence: " << avg_intelligence << " \n";
    std::cout << "average children amount: " << avg_children_amount << " \n";
    std::cout << "average children health: " << avg_children_health << " \n";
    std::cout << "average health: " << avg_health << " \n";
    std::cout << "average lifetime: " << avg_lifetime << " \n";
}

void Run::print_progress(int today) {
    if (progress - 0. >= 1e-6) {
        for (int i = 0; i < 9; ++i) {
            std::cout << "\033[F\r";
            std::cout.flush();
        }
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
    std::cout << "Number of bots today: " << all_bots.size() << " \n";
    print_average();
}

void Run::run(int map_size, int bots_amount, int days_amount, int food_amount) {
    std::cout << "START SIMULATION WITH PARAMETERS:\n";
    std::cout << "map_size = " << map_size << "\n";
    std::cout << "bots_amount = " << bots_amount << "\n";
    std::cout << "days_amount = " << days_amount << "\n";
    std::cout << "food_amount = " << food_amount << "\n";

    init(map_size, bots_amount, days_amount, food_amount);
    int64_t passes_amount = 0;

    for (int today = 0; today <= days_amount_; ++today) {
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
        std::cout << "SIMULATION FAILED. ALL BOTS DEAD!\n";
    } else {
        std::cout << "SUCCESSFUL SIMULATION. CONGRATULAIONS!\n";
    }

    std::cout << "Passes amount = " << passes_amount << "\n";
}
