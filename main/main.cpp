#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size         = 100;
    parameters::bots_amount      = 100;
    parameters::altruists_amount = 50;
    parameters::days_amount      = 5'000;
    parameters::food_amount      = 1000;
    parameters::food_per_cell    = 1;
    parameters::enemies_amount   = 20;
    parameters::damage           = 33;
    parameters::mutation         = 20;
    parameters::move_error       = 30;
    run.run();
}
