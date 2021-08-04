#include "rand.h"

namespace Rand {
    std::mt19937 random_;

    int random() {
        return std::abs(static_cast<int>(random_()));
    }
}
