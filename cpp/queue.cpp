#include "queue.h"
#include "linked_list.cpp"

template <typename T>
void Queue<T>::Enqueue(T val)
{
    if (mListHead == nullptr)
        mListHead = mListTail = new ListNode<T>(val);
    else
        mListTail = mListTail->InsertAfter(val);
}

template <typename T>
T Queue<T>::Dequeue()
{
    if (mListHead == nullptr)
        return 0; // ehhhhhh

    T toRemove = mListHead->GetValue();
    mListHead = mListHead->Remove(toRemove);
    return toRemove;
}

template <typename T>
string Queue<T>::ToString()
{
    if (mListHead == nullptr)
        return "";

    return mListHead->ListToString();
}
