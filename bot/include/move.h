#include "bot.h"
#include "map.h"
#include "position.h"

void Move(Bot& bot, Map& map, Position position) {
    map[position.x][position.y].queue.push_back(&bot);
}