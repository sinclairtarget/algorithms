#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>

using std::string;

template <typename T>
class ListNode
{
public:
    explicit ListNode(T val) : 
        mStoredValue(val),
        mNext(nullptr) {}

    explicit ListNode(T val, ListNode* next) : 
        mStoredValue(val),
        mNext(next) {}

    // Inserts the given value before this node and returns the new list head.
    ListNode* Prepend(T val);

    // Inserts the given value immediately after this node. Returns the newly
    // created node.
    ListNode* InsertAfter(T val);

    // Returns the first node with the given value, or null if the value is not
    // present.
    ListNode* Find(T val);

    // Removes the first node with the given value. Returns the new list head,
    // which may or may not be the same as the old one.
    ListNode* Remove(T val);

    // Returns the new list head.
    ListNode* Reverse();

    T GetValue() { return mStoredValue; }
    ListNode* GetNext() { return mNext; }
    void SetNext(ListNode* next) { mNext = next; }

    string ToString();     // Prints this node.
    string ListToString(); // Prints the whole list.

protected:
    T mStoredValue;
    ListNode* mNext;
};

#endif
