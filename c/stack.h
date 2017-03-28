#ifndef __STACK_H__
#define __STACK_H__

#include "linked_list.h"

typedef struct {
    ListNode* listHead;
} Stack;

typedef void (*StackYieldFunc)(void* value);

Stack* StackCreate();

void StackPush(Stack* stack, void* value);

void* StackPop(Stack* stack);

void StackEach(Stack* stack, StackYieldFunc yieldFunc);

#endif
