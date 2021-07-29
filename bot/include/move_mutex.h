#include "bot.h"
#include "map_mutex.h"
#include "position.h"
#include <mutex>

void MoveMutex(Bot& bot, Map_mutex& map, Position position) {
    std::unique_lock uniqueLock(*map[position.x][position.y].mutex);
    map[position.x][position.y].queue.push_back(&bot);
}

