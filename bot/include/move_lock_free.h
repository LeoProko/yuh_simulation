#include "bot.h"
#include "map_lock_free.h"
#include "position.h"

void MoveLockFree(Bot& bot, Map_lock_free& map, Position position) {
    map[position.x][position.y].queue->Push(&bot);
}
