#include "bot.h"

Bot::Bot(int size)
    : position_(std::rand() % size, std::rand() % size) {}
