#include <iostream>

#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size      = 10;
    parameters::bots_amount   = 100;
    parameters::days_amount   = 5'000;
    parameters::food_amount   = 100;
    parameters::food_per_cell = 10;
    parameters::damage        = 20;
    parameters::mutation      = 10;
    parameters::move_error    = 30;
    run.run();
}
