#ifndef BST_H
#define BST_H

#include "stdbool.h"

// BST that stores integers.
typedef struct BinaryTreeNode {
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
    int value;
} BinaryTreeNode;

typedef enum { INORDER, PREORDER, POSTORDER, REVORDER } IterationOrder;

typedef void (*BinaryTreeYieldFunc)(int value, int depth);

BinaryTreeNode* BinaryTreeCreate(int value);

// Inserts the given value into the tree. Returns true if the value was not
// already in the tree, false otherwise.
bool BinaryTreeInsert(BinaryTreeNode* node, int value);

// Removes the node with the given value. Returns the (possibly new) root node.
// Returns NULL if the value is not in the tree.
BinaryTreeNode* BinaryTreeRemove(BinaryTreeNode* node, int value);

// Returns NULL if the value is not in the tree. Otherwise returns the tree
// node containing the given value.
BinaryTreeNode* BinaryTreeFind(BinaryTreeNode* node, int value);

BinaryTreeNode* BinaryTreeMin(BinaryTreeNode* node);

BinaryTreeNode* BinaryTreeMax(BinaryTreeNode* node);

// Traverses the tree, passing each node to the given yieldFunc.
void BinaryTreeEach(BinaryTreeNode* node, 
                    IterationOrder order,
                    BinaryTreeYieldFunc yieldFunc);

#endif
