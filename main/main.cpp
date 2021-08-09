#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size         = 100;
    parameters::bots_amount      = 1000;
    parameters::altruists_amount = 500;
    parameters::days_amount      = 1'000;
    parameters::food_amount      = 1000;
    parameters::food_per_cell    = 1;
    parameters::enemies_amount   = 200;
    parameters::damage           = 33;
    parameters::mutation         = 20;
    parameters::move_error       = 30;
    run.run();
}
