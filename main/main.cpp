#include <iostream>

#include "run.h"

int main() {
    std::cout << "MAIN BEGIN" << "\n";
    Run run;
    int map_size = 1'000;
    int bots_amount = 1'000;
    int days_amount = 10;
    run.run(map_size, bots_amount, days_amount);
    std::cout << "MAIN END" << "\n";
}
