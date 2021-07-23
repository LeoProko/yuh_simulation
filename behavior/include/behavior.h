#pragma once

#include "bot.h"

class Behavior {
public:
    virtual void action(const Bot& bot) const = 0;
};
