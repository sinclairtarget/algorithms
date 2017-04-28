#ifndef BST_H
#define BST_H

#include "stdbool.h"

// Splay tree containing integers.
typedef struct SplayTreeNode {
    struct SplayTreeNode* left;
    struct SplayTreeNode* right;
    int value;
} SplayTreeNode;

typedef enum { INORDER, PREORDER, POSTORDER, REVORDER } IterationOrder;

typedef void (*SplayTreeYieldFunc)(SplayTreeNode* node, int depth);

SplayTreeNode* SplayTreeCreate(int value);

// Inserts the given value into the tree. Returns true if the value was not
// already in the tree, false otherwise.
bool SplayTreeInsert(SplayTreeNode** ptrToRoot, int value);

// Removes the node with the given value.
void SplayTreeRemove(SplayTreeNode** ptrToRoot, int value);

// Returns NULL if the value is not in the tree. Otherwise returns the tree
// node containing the given value.
SplayTreeNode* SplayTreeFind(SplayTreeNode** ptrToRoot, int value);

SplayTreeNode* SplayTreeMax(SplayTreeNode** ptrToRoot);
SplayTreeNode* SplayTreeMin(SplayTreeNode** ptrToRoot);

// Traverses the tree, passing each node to the given yieldFunc.
void SplayTreeEach(SplayTreeNode* node, 
                   IterationOrder order,
                   SplayTreeYieldFunc yieldFunc);

#endif
