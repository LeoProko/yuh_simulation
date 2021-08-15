#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size         = 300;
    parameters::bots_amount      = 50'000;
    parameters::altruists_amount = parameters::bots_amount / 2;
    parameters::days_amount      = 600;
    parameters::food_amount      = parameters::map_size * parameters::map_size / 10;
    parameters::food_per_cell    = 20;
    parameters::enemies_amount   = parameters::food_amount / 4;
    parameters::damage           = 30;
    parameters::mutation         = 10;
    parameters::move_error       = 20;
    run.run();
}
