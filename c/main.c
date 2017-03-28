#include <stdio.h>

#include "queue.h"

void PrintIntValue(void* value)
{
    printf("%d ", *((int*)value));
}

void PrintIntQueue(Queue* queue)
{
    QueueEach(queue, PrintIntValue);
    printf("\n");
}

int main() 
{
    Queue* queue = QueueCreate();
    PrintIntQueue(queue);

    int val = 1;
    QueueEnqueue(queue, &val);
    PrintIntQueue(queue);

    int val2 = 2;
    QueueEnqueue(queue, &val2);
    PrintIntQueue(queue);

    int val3 = 3;
    QueueEnqueue(queue, &val3);
    PrintIntQueue(queue);

    printf("dequeued: %d\n", *(int*) QueueDequeue(queue));
    PrintIntQueue(queue);

    printf("dequeued: %d\n", *(int*) QueueDequeue(queue));
    PrintIntQueue(queue);

    printf("dequeued: %d\n", *(int*) QueueDequeue(queue));
    PrintIntQueue(queue);

    QueueDequeue(queue);

    QueueEnqueue(queue, &val);
    PrintIntQueue(queue);

    printf("dequeued: %d\n", *(int*) QueueDequeue(queue));
    PrintIntQueue(queue);

    return 0;
}
