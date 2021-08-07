#include "parameters.h"

namespace parameters {
    std::mt19937 random_;
    int map_size = 10;
    int bots_amount = 100;
    int days_amount = 5'000;
    int food_amount = 100;
    int food_per_cell = 10;
    int damage = 20;
    int mutation = 10;
    int move_error = 30;

    int random() {
        return std::abs(static_cast<int>(random_()));
    }

    void print() {
        std::cout << "Map size......." << map_size << "\n";
        std::cout << "Bots amount...." << bots_amount << "\n";
        std::cout << "Days amount...." << days_amount << "\n";
        std::cout << "Food amount:..." << food_amount << "\n";
        std::cout << "Food per cell.." << food_per_cell << "\n";
        std::cout << "Damage:........" << damage << "\n";
        std::cout << "Mutation:......" << mutation << "\n";
        std::cout << "Move error:...." << move_error << "\n";
    }
}
