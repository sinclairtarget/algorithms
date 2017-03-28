#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct ListNode {
    struct ListNode* next;
    void* value;
} ListNode;

typedef void (*ListYieldFunc)(void* value);

ListNode* ListCreate(void* value);

// Returns the new list head.
ListNode* ListPrepend(ListNode* listHead, void* value);

// Inserts the value immediately after the given node. Returns the new node.
ListNode* ListInsertAfter(ListNode* node, void* value);

ListNode* ListFind(ListNode* listHead, void* value);

// Returns the (possibly new) list head.
ListNode* ListRemove(ListNode* listHead, void* value);

// Returns the new list head.
ListNode* ListReverse(ListNode* listHead);

void ListEach(ListNode* listHead, ListYieldFunc yieldFunc);

#endif
