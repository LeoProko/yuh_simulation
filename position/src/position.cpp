#include "position.h"

Position::Position(int first, int second)
    : x(first)
    , y(second) {}


bool operator<(const Position& first, const Position& second) {
    if (first.x != second.x) {
        return first.x < second.x;
    }
    return first.y < second.y;
}

bool operator==(const Position& first, const Position& second) {
    return first.x == second.x && first.y == second.y;
}