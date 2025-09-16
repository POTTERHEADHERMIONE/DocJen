#ifndef LOCKFREE_STACK_H
#define LOCKFREE_STACK_H

#include <atomic>

template <typename T>
struct StackNode {
    T data;
    StackNode* next;
    StackNode(const T& d) : data(d), next(nullptr) {}
};

template <typename T>
class LockFreeStack {
    std::atomic<StackNode<T>*> head;
public:
    LockFreeStack() : head(nullptr) {}
    void push(const T& data);
    bool pop(T& result);
};

#endif
