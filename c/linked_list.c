#include <stdlib.h>

#include "linked_list.h"

ListNode* _ListReverse(ListNode* node, ListNode** head);

ListNode* ListCreate(void* value)
{
    ListNode* node = calloc(1, sizeof(ListNode));
    node->value = value;
    return node;
}

ListNode* ListPrepend(ListNode* node, void* value) {
    ListNode* new = ListCreate(value);
    new->next = node;
    return new;
}

ListNode* ListFind(ListNode* node, void* value)
{
    ListNode* cursor;
    for (cursor = node; cursor != NULL; cursor = cursor->next)
        if (cursor->value == value) return cursor;

    return NULL;
}

ListNode* ListRemove(ListNode* node, void* value)
{
    ListNode** prevNextPtr = &node;
    ListNode* cursor;

    for (cursor = node; cursor != NULL; cursor = cursor->next) {
        if (cursor->value == value) {
            *prevNextPtr = cursor->next;
            free(cursor);
            break;
        }

        prevNextPtr = &cursor->next;
    }

    return (node != NULL) ? node : *prevNextPtr;
}

void ListEach(ListNode* node, ListYieldFunc yieldFunc)
{
    ListNode* cursor;
    for (cursor = node; cursor != NULL; cursor = cursor->next) {
        yieldFunc(cursor);
    }
}

ListNode* ListReverse(ListNode* node)
{
    ListNode* head = NULL;

    if (node != NULL)
        _ListReverse(node, &head);

    return head;
}

ListNode* _ListReverse(ListNode* node, ListNode** head)
{
    // Base case. No next node.
    if (node->next == NULL) {
        *head = node;
        return node;
    }

    // Recursive case. Put this node at the end of the reversed list.
    ListNode* end = _ListReverse(node->next, head);
    end->next = node;
    node->next = NULL;

    return node;
}
