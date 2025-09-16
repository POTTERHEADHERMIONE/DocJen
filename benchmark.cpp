#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "lockfree_queue.h"
#include "lockfree_stack.h"

constexpr int NUM_THREADS = 4;
constexpr int OPS_PER_THREAD = 100000;

void benchmark_stack() {
    LockFreeStack<int> stack;
    auto worker = [&](int id) {
        for (int i = 0; i < OPS_PER_THREAD; i++) stack.push(i + id);
    };

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; i++) threads.emplace_back(worker, i);
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Stack benchmark: " 
              << (NUM_THREADS * OPS_PER_THREAD) / diff.count() 
              << " ops/sec\n";
}

void benchmark_queue() {
    LockFreeQueue<int> queue;
    auto producer = [&](int id) {
        for (int i = 0; i < OPS_PER_THREAD; i++) queue.enqueue(i + id);
    };

    auto consumer = [&](int id) {
        int val;
        for (int i = 0; i < OPS_PER_THREAD; i++) {
            while (!queue.dequeue(val)) {}
        }
    };

    auto start = std::chrono::high_resolution_clock::now();
    std::thread p1(producer, 1), p2(producer, 2);
    std::thread c1(consumer, 1), c2(consumer, 2);
    p1.join(); p2.join(); c1.join(); c2.join();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Queue benchmark: " 
              << (2 * OPS_PER_THREAD) / diff.count() 
              << " ops/sec\n";
}

int main() {
    benchmark_stack();
    benchmark_queue();
    return 0;
}
