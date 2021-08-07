#include <iostream>

#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size      = 100;
    parameters::bots_amount   = 100;
    parameters::days_amount   = 5'000;
    parameters::food_amount   = 1000;
    parameters::food_per_cell = 1;
    parameters::damage        = 33;
    parameters::mutation      = 10;
    parameters::move_error    = 30;
    run.run();
}
