#ifndef AVL_BST_H
#define AVL_BST_H

#include "stdbool.h"

// AVL Balanced Binary Search Tree that stores integers.
typedef struct AVLTreeNode {
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    int value;
    char height;
} AVLTreeNode;

typedef enum { INORDER, PREORDER, POSTORDER, REVORDER } IterationOrder;

typedef void (*AVLTreeYieldFunc)(AVLTreeNode* node, int depth);

AVLTreeNode* AVLTreeCreate(int value);

// Inserts the given value into the tree. Returns the (possibly new) root node.
AVLTreeNode* AVLTreeInsert(AVLTreeNode* node, int value);

// Removes the node with the given value. Returns the (possibly new) root node.
// Returns NULL if the value is not in the tree.
AVLTreeNode* AVLTreeRemove(AVLTreeNode* node, int value);

// Returns NULL if the value is not in the tree. Otherwise returns the tree
// node containing the given value.
AVLTreeNode* AVLTreeFind(AVLTreeNode* node, int value);

AVLTreeNode* AVLTreeMin(AVLTreeNode* node);

AVLTreeNode* AVLTreeMax(AVLTreeNode* node);

// Traverses the tree, passing each node to the given yieldFunc.
void AVLTreeEach(AVLTreeNode* node, 
                 IterationOrder order,
                 AVLTreeYieldFunc yieldFunc);

#endif
