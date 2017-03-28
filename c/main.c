#include <stdio.h>

#include "stack.h"

void PrintIntValue(void* value)
{
    printf("%d ", *((int*)value));
}

void PrintIntStack(Stack* stack)
{
    StackEach(stack, PrintIntValue);
    printf("\n");
}

int main() 
{
    Stack* stack = StackCreate();
    PrintIntStack(stack);

    int val = 1;
    StackPush(stack, &val);
    PrintIntStack(stack);

    int val2 = 2;
    StackPush(stack, &val2);
    PrintIntStack(stack);

    int val3 = 3;
    StackPush(stack, &val3);
    PrintIntStack(stack);

    printf("popped: %d\n", *(int*) StackPop(stack));
    PrintIntStack(stack);

    printf("popped: %d\n", *(int*) StackPop(stack));
    PrintIntStack(stack);

    printf("popped: %d\n", *(int*) StackPop(stack));
    PrintIntStack(stack);

    StackPop(stack);

    StackPush(stack, &val);
    PrintIntStack(stack);

    printf("popped: %d\n", *(int*) StackPop(stack));
    PrintIntStack(stack);

    return 0;
}
