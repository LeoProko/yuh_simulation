#include "parameters.h"
#include "run.h"

int main() {
    Run run;
    parameters::map_size         = 500;
    parameters::bots_amount      = 50'000;
    parameters::altruists_amount = 25'000;
    parameters::days_amount      = 500;
    parameters::food_amount      = 75'000;
    parameters::food_per_cell    = 4;
    parameters::enemies_amount   = 25'000;
    parameters::damage           = 30;
    parameters::mutation         = 20;
    parameters::move_error       = 20;
    run.run();
}
