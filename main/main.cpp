#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size         = 100;
    parameters::bots_amount      = 5'000;
    parameters::altruists_amount = 2'500;
    parameters::days_amount      = 1'000;
    parameters::food_amount      = parameters::map_size * parameters::map_size / 10;
    parameters::food_per_cell    = 20;
    parameters::enemies_amount   = parameters::food_amount / 5;
    parameters::damage           = 30;
    parameters::mutation         = 10;
    parameters::move_error       = 20;
    run.run();
}
