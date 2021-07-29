#include <iostream>
#include <vector>
#include <memory>

#include "bot.h"
#include "map.h"

class Run {
private:
    int map_size_;
    int bots_amount_;
    int days_amount_;
    Map today_map_;
    Map tomorrow_map_ = today_map_;

    void init(int map_size, int bots_amount, int days_amount) {
        std::cout << "INITIALIZATION BEGIN" << "\n";
        map_size_ = map_size;
        bots_amount_ = bots_amount;
        days_amount_ = days_amount;
        today_map_ = Map(map_size_, bots_amount_, bots_amount_);
        std::cout << "INITIALIZATION END" << "\n";
    }

public:
    Run() = default;

    void run(int map_size, int bots_amount, int days_amount) {
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
                cell.move();
                ++passes_amount;
            }
            for (auto& cell : today_map_) {
                cell.do_all();
                ++passes_amount;
            }
        }
        std::cout << "Passes amount = " << passes_amount << "\n";
        std::cout << "RUN END" << "\n";
    }
};

int main() {
    std::cout << "MAIN BEGIN" << "\n";
    Run run;
    int map_size = 3'000;
    int bots_amount = 1'000'000;
    int days_amount = 10;
    run.run(map_size, bots_amount, days_amount);
    std::cout << "MAIN END" << "\n";
}
