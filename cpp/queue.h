#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

template <typename T>
class Queue
{
public:
    Queue() : 
        mListHead(nullptr),
        mListTail(nullptr) {}

    void Enqueue(T val);
    T Dequeue();

    string ToString();

protected:
    ListNode<T>* mListHead;
    ListNode<T>* mListTail; // So Enqueue() can be O(1)
};

#endif
