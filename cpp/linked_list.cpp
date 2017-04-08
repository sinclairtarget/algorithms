#include "linked_list.h"

template <typename T>
ListNode<T>* _Reverse(ListNode<T>* node, ListNode<T>** listHead);

template <typename T>
ListNode<T>* ListNode<T>::Prepend(T val)
{
    return new ListNode<T>(val, this);
}

template <typename T>
ListNode<T>* ListNode<T>::InsertAfter(T val)
{
    ListNode* newNode = new ListNode<T>(val, mNext);
    mNext = newNode;
    return newNode;
}

template <typename T>
ListNode<T>* ListNode<T>::Find(T val)
{
    for (ListNode<T>* cursor = this;
         cursor != nullptr;
         cursor = cursor->GetNext()) 
    {
        if (cursor->GetValue() == val) return cursor;
    }

    return nullptr;
}

template <typename T>
ListNode<T>* ListNode<T>::Remove(T val)
{
    ListNode<T>* previous = nullptr;
    ListNode<T>* listHead = this;

    for (ListNode<T>* cursor = this;
         cursor != nullptr;
         cursor = cursor->GetNext()) 
    {
        if (cursor->GetValue() == val) {
            if (previous != nullptr)
                previous->SetNext(cursor->GetNext());
            else
                listHead = cursor->GetNext();

            delete cursor;
            break;
        }

        previous = cursor;
    }

    return listHead;
}

template <typename T>
ListNode<T>* ListNode<T>::Reverse()
{
    ListNode<T>* listHead = this;
    _Reverse(listHead, &listHead);
    return listHead;
}

template <typename T>
string ListNode<T>::ToString()
{
    return std::to_string(mStoredValue);
}

template <typename T>
string ListNode<T>::ListToString()
{
    string str;
    for (ListNode<T>* cursor = this;
         cursor != nullptr;
         cursor = cursor->GetNext()) {
        str += cursor->ToString();
        str += "->";
    }

    return str;
}

template <typename T>
ListNode<T>* _Reverse(ListNode<T>* node, ListNode<T>** listHead)
{
    // Base case. This is the only node.
    if (node->GetNext() == nullptr) {
        *listHead = node;
        return node;
    }

    // Recursive case. Put this node at the end of the list.
    ListNode<T>* lastNode = _Reverse(node->GetNext(), listHead);
    lastNode->SetNext(node);
    node->SetNext(nullptr);

    return node;
}
