#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

typedef struct {
    ListNode* listHead;
    ListNode* listTail; // So we can Enqueue() in O(1)
} Queue;

typedef void (*QueueYieldFunc)(void* value);

Queue* QueueCreate();

void QueueEnqueue(Queue* queue, void* value);

void* QueueDequeue(Queue* queue);

void QueueEach(Queue* queue, QueueYieldFunc yieldFunc);

#endif
