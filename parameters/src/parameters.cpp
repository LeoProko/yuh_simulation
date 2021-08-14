#include "parameters.h"

namespace parameters {
    std::mt19937 random_;
    int map_size = 10;
    int bots_amount = 100;
    int altruists_amount = 25;
    int days_amount = 30;
    int food_amount = 100;
    int food_per_cell = 10;
    int enemies_amount = 10;
    int damage = 20;
    int mutation = 10;
    int move_error = 30;
    int threads_amount = 8;
    std::mutex reproduce_mutex;

    int random() {
        return std::abs(static_cast<int>(random_()));
    }

    void print() {
        std::cout << "Map size.........." << map_size << "\n";
        std::cout << "Bots amount......." << bots_amount << "\n";
        std::cout << "Altruists amount.." << altruists_amount << "\n";
        std::cout << "Days amount......." << days_amount << "\n";
        std::cout << "Food amount:......" << food_amount << "\n";
        std::cout << "Enemies amount...." << enemies_amount << "\n";
        std::cout << "Food per cell....." << food_per_cell << "\n";
        std::cout << "Damage:..........." << damage << "\n";
        std::cout << "Mutation:........." << mutation << "\n";
        std::cout << "Move error:......." << move_error << "\n";
    }
}
