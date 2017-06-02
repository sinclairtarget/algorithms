#include <stdio.h>

#include "red_black_bst.h"
#include "string.h"

void PrintNode(RedBlackTreeNode* node, int depth)
{
    int multiple = 2;
    char out[depth * multiple + 100];
    for (int i = 0; i < depth * multiple; i++)
        out[i] = ' ';

    out[depth * multiple] = '\0';

    strcat(out, "%d (%c)\n");

    printf(out, node->value, (node->color == BLACK) ? 'b' : 'r');
}

int main()
{
    RedBlackTreeNode* root = RedBlackTreeCreate(5);

    RedBlackTreeInsert(&root, 2);
    RedBlackTreeInsert(&root, 7);
    RedBlackTreeInsert(&root, 6);
    RedBlackTreeInsert(&root, 8);
    RedBlackTreeInsert(&root, 1);
    RedBlackTreeInsert(&root, 3);
    RedBlackTreeInsert(&root, 4);
    RedBlackTreeEach(root, REVORDER, PrintNode);

    printf("\n");

    RedBlackTreeRemove(&root, 2);
    RedBlackTreeEach(root, REVORDER, PrintNode);

    return 0;
}
