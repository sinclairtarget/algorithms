#include <stdio.h>

#include "splay_bst.h"
#include "string.h"

void PrintNode(SplayTreeNode* node, int depth)
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
    SplayTreeNode* root = SplayTreeCreate(4);
    
    SplayTreeInsert(&root, 3);
    SplayTreeInsert(&root, 2);
    SplayTreeInsert(&root, 1);
    
    SplayTreeEach(root, REVORDER, PrintNode);

    SplayTreeRemove(&root, 4);

    SplayTreeEach(root, REVORDER, PrintNode);

    return 0;
}
