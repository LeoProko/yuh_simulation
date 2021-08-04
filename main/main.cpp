#include <iostream>

#include "run.h"

int main() {
    Run run;
    int map_size = 100;
    int bots_amount = 1000;
    int days_amount = 80000;
    run.run(map_size, bots_amount, days_amount);
}
