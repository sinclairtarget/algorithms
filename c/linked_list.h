#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct ListNode {
    struct ListNode* next;
    void* value;
} ListNode;

typedef void (*ListYieldFunc)(ListNode* node);

ListNode* ListCreate(void* value);

ListNode* ListPrepend(ListNode* node, void* value);

ListNode* ListFind(ListNode* node, void* value);

ListNode* ListRemove(ListNode* node, void* value);

void ListEach(ListNode* node, ListYieldFunc yieldFunc);

ListNode* ListReverse(ListNode* node);

#endif
