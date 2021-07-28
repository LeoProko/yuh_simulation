#include "behaviours.h"

void reproduce(Cell& cell) {
    if (cell.bots_.size() >= 2) {
        cell.bots.emplace_back(*(cell.bots_.begin()), *(cell.bots_.begin() + 1));
        cell.
    }
}

void split_food(Cell& cell) {
    // Split food
}
