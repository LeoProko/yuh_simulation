#include "run.h"

void Run::init(int map_size, int bots_amount, int days_amount) {
    std::cout << "INITIALIZATION BEGIN" << "\n";
    map_size_ = map_size;
    bots_amount_ = bots_amount;
    days_amount_ = days_amount;
    today_map_ = Map(map_size_, bots_amount_, bots_amount_);
    std::cout << "INITIALIZATION END" << "\n";
}

void Run::run(int map_size, int bots_amount, int days_amount) {
    std::cout << "RUN BEGIN" << "\n";
    std::cout << "START SIMULATION WITH PARAMETERS:\n";
    std::cout << "map_size = " << map_size << "\n";
    std::cout << "bots_amount = " << bots_amount << "\n";
    std::cout << "days_amount = " << days_amount << "\n";
    init(map_size, bots_amount, days_amount);
    int64_t passes_amount = 0;
    for (int today = 1; today <= days_amount_; ++today) {
        std::cout << "Day number " << today << "\n";
        for (auto& cell : today_map_) {
            for (auto& bot : cell.bots_) {
                move(bot, today_map_);
            }
            ++passes_amount;
        }
        for (auto& cell : today_map_) {
            cell.do_all(all_bots);
            ++passes_amount;
        }
    }
    std::cout << "Passes amount = " << passes_amount << "\n";
    std::cout << "RUN END" << "\n";
}
