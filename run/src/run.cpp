#include "run.h"

void Run::init(std::list<Bot>& all_bots, int map_size, int bots_amount, int days_amount) {
    std::cout << "INITIALIZATION BEGIN\n";
    map_size_ = map_size;
    bots_amount_ = bots_amount;
    days_amount_ = days_amount;
    today_map_ = Map(all_bots, map_size_, bots_amount_, bots_amount_);
    std::cout << "INITIALIZATION END\n";
}

void Run::run(int map_size, int bots_amount, int days_amount) {
    std::cout << "RUN BEGIN\n";
    std::cout << "START SIMULATION WITH PARAMETERS:\n";
    std::cout << "map_size = " << map_size << "\n";
    std::cout << "bots_amount = " << bots_amount << "\n";
    std::cout << "days_amount = " << days_amount << "\n";

    std::list<Bot> all_bots;
    init(all_bots, map_size, bots_amount, days_amount);
    int64_t passes_amount = 0;

    for (int today = 1; today <= days_amount_; ++today) {
        std::cout << "Day number " << today << "\n";
        for (auto& bot : all_bots) {
            move(bot, today_map_);
            today_map_[bot.position_].bots_.push_back(&bot);
        }

        std::list<Bot> new_bots;
        for (auto& bot : all_bots) {
            today_map_[bot.position_].do_all(new_bots);
            ++passes_amount;
        }
        for (const auto& new_bot : new_bots) {
            all_bots.push_back(new_bot);
        }
        std::cout << "\tNumber of bots today: " << all_bots.size() << "\n";
    }
    std::cout << "Passes amount = " << passes_amount << "\n";
    std::cout << "RUN END\n";
}
