#include <stdlib.h>

#include "linked_list.h"

ListNode* _ListReverse(ListNode* listHead, ListNode** head);

ListNode* ListCreate(void* value)
{
    ListNode* listHead = calloc(1, sizeof(ListNode));
    listHead->value = value;
    return listHead;
}

ListNode* ListPrepend(ListNode* listHead, void* value) 
{
    ListNode* newListHead = ListCreate(value);
    newListHead->next = listHead;
    return newListHead;
}

ListNode* ListInsertAfter(ListNode* node, void* value) 
{
    ListNode* newNode = ListCreate(value);
    newNode->next = node->next;
    node->next = newNode;
    return newNode;
}

ListNode* ListFind(ListNode* listHead, void* value)
{
    ListNode* cursor;
    for (cursor = listHead; cursor != NULL; cursor = cursor->next)
        if (cursor->value == value) return cursor;

    return NULL;
}

ListNode* ListRemove(ListNode* listHead, void* value)
{
    ListNode** prevNextPtr = &listHead;
    ListNode* cursor;

    for (cursor = listHead; cursor != NULL; cursor = cursor->next) {
        if (cursor->value == value) {
            *prevNextPtr = cursor->next;
            free(cursor);
            break;
        }

        prevNextPtr = &cursor->next;
    }

    return (listHead != NULL) ? listHead : *prevNextPtr;
}

ListNode* ListReverse(ListNode* listHead)
{
    ListNode* newListHead = NULL;

    if (listHead != NULL)
        _ListReverse(listHead, &newListHead);

    return newListHead;
}

ListNode* _ListReverse(ListNode* node, ListNode** listHead)
{
    // Base case. No next node.
    if (node->next == NULL) {
        *listHead = node;
        return node;
    }

    // Recursive case. Put this node at the end of the reversed list.
    ListNode* end = _ListReverse(node->next, listHead);
    end->next = node;
    node->next = NULL;

    return node;
}

void ListEach(ListNode* node, ListYieldFunc yieldFunc)
{
    ListNode* cursor;
    for (cursor = node; cursor != NULL; cursor = cursor->next) {
        yieldFunc(cursor->value);
    }
}
