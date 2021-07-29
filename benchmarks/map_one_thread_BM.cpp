#include "bot.h"
#include "map.h"
#include <vector>
#include <cstdlib>
#include "move.h"
#include <benchmark/benchmark.h>

static void BM_map_one_thread(benchmark::State& state) {
    size_t map_sz = state.range(0);
    size_t bots_amount = state.range(1);

    std::vector<Bot> bots(bots_amount);

    Map map(map_sz, bots_amount, 0);

    for (auto _ : state) {
        for (Bot& bot : bots) {
            int new_x = rand() % map_sz;
            int new_y = rand() % map_sz;
            Move(bot, map, Position{new_x, new_y});
        }
    }
}

BENCHMARK(BM_map_one_thread)
        ->Args({100, 5000})
        ->Args({500, 10000})
        ->Args({1000, 500000});

// Run the benchmark
BENCHMARK_MAIN();