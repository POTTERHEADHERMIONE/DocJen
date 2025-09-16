#include "lockfree_queue.h"

// Michael-Scott lock-free queue
template <typename T>
LockFreeQueue<T>::LockFreeQueue() {
    QueueNode<T>* dummy = new QueueNode<T>(T());
    head.store(dummy);
    tail.store(dummy);
}

template <typename T>
void LockFreeQueue<T>::enqueue(const T& data) {
    QueueNode<T>* new_node = new QueueNode<T>(data);
    QueueNode<T>* old_tail;
    while (true) {
        old_tail = tail.load(std::memory_order_acquire);
        QueueNode<T>* next = old_tail->next.load(std::memory_order_acquire);
        if (old_tail == tail.load(std::memory_order_acquire)) {
            if (next == nullptr) {
                if (old_tail->next.compare_exchange_weak(next, new_node)) {
                    tail.compare_exchange_weak(old_tail, new_node);
                    return;
                }
            } else {
                tail.compare_exchange_weak(old_tail, next);
            }
        }
    }
}

template <typename T>
bool LockFreeQueue<T>::dequeue(T& result) {
    while (true) {
        QueueNode<T>* old_head = head.load(std::memory_order_acquire);
        QueueNode<T>* old_tail = tail.load(std::memory_order_acquire);
        QueueNode<T>* next = old_head->next.load(std::memory_order_acquire);

        if (old_head == head.load(std::memory_order_acquire)) {
            if (old_head == old_tail) {
                if (next == nullptr) return false; // empty
                tail.compare_exchange_weak(old_tail, next);
            } else {
                result = next->data;
                if (head.compare_exchange_weak(old_head, next)) {
                    delete old_head;
                    return true;
                }
            }
        }
    }
}

// Explicit instantiation
template class LockFreeQueue<int>;
