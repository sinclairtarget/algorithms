#include <stdio.h>

#include "avl_bst.h"
#include "string.h"

void PrintNode(AVLTreeNode* node, int depth)
{
    char out[depth + 100];
    for (int i = 0; i < depth; i++)
        out[i] = ' ';

    out[depth] = '\0';

    strcat(out, "%d\n");

    printf(out, node->value);
}

int main() 
{
    AVLTreeNode* root = AVLTreeCreate(4);

    root = AVLTreeInsert(root, 6);
    root = AVLTreeInsert(root, 5);
    root = AVLTreeInsert(root, 7);
    root = AVLTreeInsert(root, 8);
    root = AVLTreeInsert(root, 9);
    root = AVLTreeInsert(root, 2);
    root = AVLTreeInsert(root, 3);

    AVLTreeEach(root, REVORDER, PrintNode);

    return 0;
}
