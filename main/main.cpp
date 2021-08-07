#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size         = 10;
    parameters::bots_amount      = 100;
    parameters::altruists_amount = 50;
    parameters::days_amount      = 1'000;
    parameters::food_amount      = 100;
    parameters::food_per_cell    = 10;
    parameters::enemies_amount   = 20;
    parameters::damage           = 20;
    parameters::mutation         = 20;
    parameters::move_error       = 30;
    run.run();
}
