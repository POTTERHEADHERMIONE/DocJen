#include <cassert>
#include <iostream>
#include "lockfree_stack.h"
#include "lockfree_queue.h"

void test_stack_basic() {
    LockFreeStack<int> s;
    int val;
    assert(!s.pop(val));
    s.push(42);
    assert(s.pop(val) && val == 42);
    std::cout << "Stack basic test passed\n";
}

void test_queue_basic() {
    LockFreeQueue<int> q;
    int val;
    assert(!q.dequeue(val));
    q.enqueue(10);
    q.enqueue(20);
    assert(q.dequeue(val) && val == 10);
    assert(q.dequeue(val) && val == 20);
    std::cout << "Queue basic test passed\n";
}

int main() {
    test_stack_basic();
    test_queue_basic();
    std::cout << "All tests passed!\n";
    return 0;
}
