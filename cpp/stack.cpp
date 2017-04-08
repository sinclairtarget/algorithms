#include "stack.h"

template <typename T>
void Stack<T>::Push(T val)
{
    if (mListHead == nullptr)
        mListHead = new ListNode<T>(val);
    else
        mListHead = mListHead->Prepend(val);
}

template <typename T>
T Stack<T>::Pop()
{
    if (mListHead == nullptr)
        return 0;

    T toRemove = mListHead->GetValue();
    mListHead = mListHead->Remove(toRemove);
    return toRemove;
}

template <typename T>
string Stack<T>::ToString()
{
    if (mListHead == nullptr) 
        return "";

    return mListHead->ListToString();
}
