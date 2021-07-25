#include <iostream>
#include <vector>

#include "bot.h"
#include "map.h"

int main() {
    std::cout << "MAIN BEGIN\n";

    const int MAP_SIZE = 10'000;
    const int BOT_COUNTER = 10'000;
    const int NUMBER_OF_DAYS = 365;

    std::cout << "check 1" << std::endl;
    Map map(MAP_SIZE, BOT_COUNTER, 0);
    std::cout << "check 2" << std::endl;
    std::vector<Bot> bots(BOT_COUNTER, Bot(MAP_SIZE));
    std::cout << "check 3" << std::endl;

    int64_t number_of_passes = 0;

    for (int today = 1; today <= NUMBER_OF_DAYS; ++today) {
        for (const Bot& bot : bots) {
            if (bot.health_ <= 0) {
                // remove bot
            }
            ++number_of_passes;
        }
    }
    std::cout << "Number of passes = " << number_of_passes << "\n";

    std::cout << "MAIN END\n";
}
