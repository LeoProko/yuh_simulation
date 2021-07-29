#include "cell.h"

bool bot_attractiveness_comparator(const Bot& first, const Bot& second) {
    return first.attractiveness_ < second.attractiveness_;
}

void Cell::reproduce() {

}

void Cell::split_food() {

}

void Cell::do_all() {
    reproduce();
    split_food();    
}