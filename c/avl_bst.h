#ifndef AVL_BST_H
#define AVL_BST_H

#include "stdbool.h"

// AVL Balanced Binary Search Tree that stores integers.
//
// AVL trees enforce a "balance condition" to ensure that operations on the
// tree have O(log(n)) complexity even over sorted inputs.
//
// Maintanance to ensure that the tree conforms to the balance conditions is
// done on each insert and remove. Each node keeps track of the height of its
// deepest subtree.
//
// Typically the balance condition is that no node's left subtree can be more
// than one level deeper than its right subtree (and vice versa).
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
