#include <stdlib.h>

#include "stack.h"

Stack* StackCreate() 
{
    return calloc(1, sizeof(Stack));
}

void StackPush(Stack* stack, void* value)
{
    if (stack->listHead == NULL)
        stack->listHead = ListCreate(value);
    else
        stack->listHead = ListPrepend(stack->listHead, value);
}

void* StackPop(Stack* stack)
{
    if (stack->listHead == NULL) return NULL;

    void* toRemove = stack->listHead->value;
    stack->listHead = ListRemove(stack->listHead, toRemove);
    return toRemove;
}

void StackEach(Stack* stack, StackYieldFunc yieldFunc)
{
    ListEach(stack->listHead, yieldFunc);
}
