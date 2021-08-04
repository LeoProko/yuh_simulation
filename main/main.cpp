#include <iostream>

#include "run.h"

int main() {
    Run run;
    int map_size = 50;
    int bots_amount = 5'000;
    int days_amount = 1000;
    run.run(map_size, bots_amount, days_amount);
}
