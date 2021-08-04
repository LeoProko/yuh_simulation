#include <iostream>

#include "run.h"

int main() {
    Run run;
    int map_size = 10;
    int bots_amount = 100;
    int days_amount = 5'000;
    int food_amount = map_size * map_size;
    run.run(map_size, bots_amount, days_amount, food_amount);
}
