#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

template <typename T>
class Stack
{
public:
    Stack() : mListHead(nullptr) {}

    void Push(T val);
    T Pop();

    string ToString();
protected:
    ListNode<T>* mListHead;
};

#endif 
