#include <iostream>

#include "run.h"

int main() {
    std::cout << "MAIN BEGIN" << "\n";
    Run run;
    int map_size = 5;
    int bots_amount = 10;
    int days_amount = 100;
    run.run(map_size, bots_amount, days_amount);
    std::cout << "MAIN END" << "\n";
}
