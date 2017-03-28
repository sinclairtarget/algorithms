#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct ListNode {
    struct ListNode* next;
    void* value;
} ListNode;

typedef void (*ListYieldFunc)(void* value);

ListNode* ListCreate(void* value);

// Returns the new list head.
ListNode* ListPrepend(ListNode* node, void* value);

ListNode* ListFind(ListNode* node, void* value);

// Returns the (possibly new) list head.
ListNode* ListRemove(ListNode* node, void* value);

// Returns the new list head.
ListNode* ListReverse(ListNode* node);

void ListEach(ListNode* node, ListYieldFunc yieldFunc);

#endif
