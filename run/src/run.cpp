#include "run.h"

void Run::init() {
    std::cout << "INITIALIZATION BEGIN\n";
    progress = 0.;
    progress_scale = 1. / parameters::days_amount;
    today_map_ = Map();
    for (int i = 0; i < parameters::bots_amount; ++i) {
        all_bots.emplace_back();
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
    std::cout << "Average militancy: " << avg_militancy << " \n";
    std::cout << "Average intelligence: " << avg_intelligence << " \n";
    std::cout << "Average children amount: " << avg_children_amount << " \n";
    std::cout << "Average children health: " << avg_children_health << " \n";
    std::cout << "Average health: " << avg_health << " \n";
    std::cout << "Average lifetime: " << avg_lifetime << " \n";
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

void Run::run() {
    std::cout << "START SIMULATION WITH PARAMETERS:\n";
    parameters::print();

    init();
    int64_t passes_amount = 0;

    for (int today = 0; today <= parameters::days_amount; ++today) {
        print_progress(today);
        for (auto bot_iter = all_bots.begin(); bot_iter != all_bots.end();) {
            if (bot_iter->health_ > parameters::damage) {
                move(*bot_iter, today_map_);
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
