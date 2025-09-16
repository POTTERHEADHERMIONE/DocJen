#include "lockfree_stack.h"

template <typename T>
void LockFreeStack<T>::push(const T& data) {
    StackNode<T>* new_node = new StackNode<T>(data);
    new_node->next = head.load(std::memory_order_relaxed);
    while (!head.compare_exchange_weak(new_node->next, new_node,
                                       std::memory_order_release,
                                       std::memory_order_relaxed)) {}
}

template <typename T>
bool LockFreeStack<T>::pop(T& result) {
    StackNode<T>* old_head = head.load(std::memory_order_relaxed);
    while (old_head &&
           !head.compare_exchange_weak(old_head, old_head->next,
                                       std::memory_order_acquire,
                                       std::memory_order_relaxed)) {}
    if (!old_head) return false;
    result = old_head->data;
    delete old_head;
    return true;
}

// Explicit instantiation
template class LockFreeStack<int>;
