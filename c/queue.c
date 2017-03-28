#include <stdlib.h>

#include "queue.h"

Queue* QueueCreate()
{
    return calloc(1, sizeof(Queue));
}

void QueueEnqueue(Queue* queue, void* value)
{
    if (queue->listHead == NULL)
        queue->listHead = queue->listTail = ListCreate(value);
    else
        queue->listTail = ListInsertAfter(queue->listTail, value);
}

void* QueueDequeue(Queue* queue)
{
    if (queue->listHead == NULL) return NULL;

    void* toRemove = queue->listHead->value;
    queue->listHead = ListRemove(queue->listHead, toRemove);
    return toRemove;
}

void QueueEach(Queue* queue, QueueYieldFunc yieldFunc)
{
    ListEach(queue->listHead, yieldFunc);
}
