#pragma once

#include <cstdlib>

#include "behavior.h"
#include "map.h"

class Fight : public Behavior {
public:
    void action(const Bot& bot, Map& map);
};
