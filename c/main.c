#include <stdio.h>

#include "linked_list.h"

void PrintIntListValue(ListNode* node)
{
    printf("%d ", *((int*)node->value));
}

void PrintIntList(ListNode* node)
{
    ListEach(node, PrintIntListValue);
    printf("\n");
}

int main() 
{
    int val = 1;
    ListNode* listHead = ListCreate(&val);

    int val2 = 2;
    listHead = ListPrepend(listHead, &val2);

    int val3 = 3;
    listHead = ListPrepend(listHead, &val3);

    PrintIntList(listHead);

    listHead = ListReverse(listHead);
    PrintIntList(listHead);

    return 0;
}
