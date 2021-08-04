#pragma once

#include <random>

namespace Rand {
    extern std::mt19937 random_;

    int random();
}
