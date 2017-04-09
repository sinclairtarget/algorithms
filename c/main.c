#include <stdio.h>

#include "bst.h"
#include "string.h"

void PrintNodeValue(int value, int depth)
{
    char out[depth + 100];
    for (int i = 0; i < depth; i++)
        out[i] = ' ';

    out[depth] = '\0';

    strcat(out, "%d\n");

    printf(out, value);
}

int main() 
{
    BinaryTreeNode* root = BinaryTreeCreate(5);

    BinaryTreeInsert(root, 6);
    BinaryTreeInsert(root, 4);
    BinaryTreeInsert(root, 2);
    BinaryTreeInsert(root, 1);
    BinaryTreeInsert(root, 8);
    BinaryTreeInsert(root, 7);
    BinaryTreeInsert(root, 3);

    BinaryTreeEach(root, REVORDER, PrintNodeValue);

    BinaryTreeNode* found = BinaryTreeFind(root, 6);
    printf("found: %d\n", found->value);

    BinaryTreeNode* min = BinaryTreeMin(root);
    printf("min: %d\n", min->value);

    BinaryTreeNode* max = BinaryTreeMax(root);
    printf("max: %d\n", max->value);

    root = BinaryTreeRemove(root, 2);
    BinaryTreeEach(root, REVORDER, PrintNodeValue);

    return 0;
}
