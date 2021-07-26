#include <iostream>
#include <vector>
#include <memory>

#include "behavior.h"
#include "bot.h"
#include "map.h"

class Run {
private:
    int map_size_;
    int bot_counter_;
    int number_of_days_;
    Map today_map_;
    Map tomorrow_map_ = today_map_;
    std::vector<Bot> bots_;
    Behavior behavior_base_;
    std::vector<std::unique_ptr<Behavior>> behaivors_;

    void init(int map_size, int bot_counter, int number_of_days) {
        std::cout << "INITIALIZATION BEGIN" << std::endl;
        map_size_ = map_size;
        bot_counter_ = bot_counter;
        number_of_days_ = number_of_days;
        bots_.resize(bot_counter_, Bot(map_size_));
        today_map_ = Map(map_size_, bot_counter_, bot_counter_);
        tomorrow_map_ = today_map_;
        behavior_base_ = Behavior(&today_map_, &tomorrow_map_);
        behaivors_ = behavior_base_.get_behaviors();
        std::cout << "INITIALIZATION END" << std::endl;
    }

public:
    Run() = default;

    void run(int map_size, int bot_counter, int number_of_days) {
        init(map_size, bot_counter, number_of_days);
        int64_t number_of_passes = 0;
        for (int today = 1; today <= number_of_days_; ++today) {
            std::cout << "Day number " << today << std::endl;
            for (const Bot& bot : bots_) {
                if (bot.health_ <= 0) {
                    // remove bot
                }
                ++number_of_passes;
            }
            for (Bot& bot : bots_) {
                for (auto& behaivor : behaivors_) {
                    behaivor->action(bot);
                    ++number_of_passes;
                }
            }
        }
        std::cout << "Number of passes = " << number_of_passes << std::endl;
    }
};

int main() {
    std::cout << "MAIN BEGIN" << std::endl;
    Run run;
    std::cout << "RUN BEGIN" << std::endl;
    run.run(10'000, 1'000'000, 20);
    std::cout << "RUN END" << std::endl;
    std::cout << "MAIN END" << std::endl;
}
