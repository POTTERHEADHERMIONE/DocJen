#include <iostream>
#include <thread>
#include <vector>
#include "lockfree_stack.h"
#include "lockfree_queue.h"

void test_stack() {
    LockFreeStack<int> stack;
    auto worker = [&](int id) {
        for (int i = 0; i < 100; i++) stack.push(id * 100 + i);
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; i++) threads.emplace_back(worker, i);
    for (auto& t : threads) t.join();

    int value, count = 0;
    while (stack.pop(value)) count++;
    std::cout << "Stack test: popped " << count << " items\n";
}

void test_queue() {
    LockFreeQueue<int> queue;
    auto producer = [&](int id) {
        for (int i = 0; i < 100; i++) queue.enqueue(id * 100 + i);
    };
    auto consumer = [&](int id) {
        int val, local_count = 0;
        while (local_count < 100) {
            if (queue.dequeue(val)) local_count++;
        }
        std::cout << "Consumer " << id << " consumed " << local_count << " items\n";
    };

    std::thread p1(producer, 1), p2(producer, 2);
    std::thread c1(consumer, 1), c2(consumer, 2);
    p1.join(); p2.join(); c1.join(); c2.join();
}

int main() {
    test_stack();
    test_queue();
    return 0;
}
