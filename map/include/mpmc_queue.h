#pragma once

#include <optional>
#include <cstdint>
#include <vector>
#include <atomic>
#include <thread>


template <class T>
class MPMCQueue {
public:
    MPMCQueue(uint64_t max_size = 128) : queue_(max_size) {
        sz_ = max_size;
        for (uint64_t i = 0; i != sz_; ++i) {
            queue_[i].tag = i;
        }
    }


    bool Push(const T& value) {
        for (;;) {
            uint64_t cur_head = head_.load();
            uint64_t idx = cur_head & (sz_ - 1);
            if (queue_[idx].tag != cur_head) {
                if (cur_head == tail_.load() + sz_) {
                    return false;
                } else {
                    std::this_thread::yield();
                    continue;
                }
            } else {
                if (head_.compare_exchange_weak(cur_head, cur_head + 1)) {
                    queue_[idx].value = value;
                    ++queue_[idx].tag;
                    return true;
                } else {
                    std::this_thread::yield();
                    continue;
                }
            }
        }
    }

    std::optional<T> Pop() {
        for (;;) {
            uint64_t cur_tail = tail_.load();
            uint64_t idx = cur_tail & (sz_ - 1);
            if (queue_[idx].tag != cur_tail + 1) {
                if (cur_tail == head_.load()) {
                    return std::nullopt;
                } else {
                    std::this_thread::yield();
                    continue;
                }
            } else {
                if (tail_.compare_exchange_weak(cur_tail, cur_tail + 1)) {
                    std::optional<T> res;
                    res = queue_[idx].value;
                    queue_[idx].tag += sz_ - 1;
                    return res;
                } else {
                    std::this_thread::yield();
                    continue;
                }
            }
        }
    }

private:
    struct Elem {
        T value;
        std::atomic<uint64_t> tag;
    };

    std::vector<Elem> queue_;
    std::atomic<uint64_t> head_ = 0;
    std::atomic<uint64_t> tail_ = 0;
    uint64_t sz_;
};