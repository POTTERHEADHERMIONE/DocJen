#ifndef LOCKFREE_QUEUE_H
#define LOCKFREE_QUEUE_H

#include <atomic>

template <typename T>
struct QueueNode {
    T data;
    std::atomic<QueueNode<T>*> next;
    QueueNode(const T& d) : data(d), next(nullptr) {}
};

template <typename T>
class LockFreeQueue {
    std::atomic<QueueNode<T>*> head;
    std::atomic<QueueNode<T>*> tail;
public:
    LockFreeQueue();
    void enqueue(const T& data);
    bool dequeue(T& result);
};

#endif
