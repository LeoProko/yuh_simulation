#include "bot.h"
#include "map_mutex.h"
#include <vector>
#include <thread>
#include <cstdlib>
#include "move_mutex.h"
#include <benchmark/benchmark.h>

static void BM_mutex(benchmark::State& state) {
    size_t map_sz = state.range(0);
    size_t bots_amount = state.range(1);

    std::vector<Bot> bots(bots_amount);

    Map_mutex map(map_sz, bots_amount, 0);

    size_t n_threads = 8;
    size_t sub_vec_sz = bots_amount / n_threads;
    size_t first_sub_vec_sz = bots_amount / n_threads + bots_amount % n_threads;
    std::vector<std::thread> threads(n_threads);

    for (auto _ : state) {

        for (size_t threads_cnt = 0; threads_cnt != n_threads; ++threads_cnt)  {
            size_t from = (threads_cnt == 0 ? 0  : first_sub_vec_sz + (threads_cnt - 1) * sub_vec_sz);
            size_t to = (threads_cnt == 0 ? first_sub_vec_sz : sub_vec_sz) + from;
            threads[threads_cnt] = std::thread(
                    [from, to, &bots, &map, &map_sz] {
                        for (size_t i = from; i != to; ++i) {
                            int new_x = rand() % map_sz;
                            int new_y = rand() % map_sz;
                            MoveMutex(bots[i], map, Position{new_x, new_y});;
                        }
                    });
        }
        for (auto& thread : threads) {
            thread.join();
        }

        for (size_t i = 0; i != map_sz; ++i) {
            for (size_t j = 0; j != map_sz; ++j) {
                map[i][j].queue.clear();
            }
        }
    }
}

BENCHMARK(BM_mutex)
        ->Args({100, 5000})
        ->Args({500, 10000})
        ->Args({1000, 500000});

// Run the benchmark
BENCHMARK_MAIN();