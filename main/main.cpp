#include <iostream>

#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size         = 20;
    parameters::bots_amount      = 500;
    parameters::altruists_amount = 250;
    parameters::days_amount      = 1'000;
    parameters::food_amount      = 1'000;
    parameters::food_per_cell    = 10;
    parameters::enemies_amount   = 50;
    parameters::damage           = 20;
    parameters::mutation         = 20;
    parameters::move_error       = 30;
    run.run();
}
