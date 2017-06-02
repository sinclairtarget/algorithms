#ifndef AVL_BST_H
#define AVL_BST_H

#include "stdbool.h"

// Red-Black tree storing integers.
//
// A red-black tree is a kind of balanced binary search tree. Like an AVL tree,
// a red-black tree has a balance condition that must not be violated by any
// operation on the tree. The balance condition ensures that no operation on
// the tree performs worse than O(log n).
//
// The balance condition for a red-black tree is specified by four rules:
// 1. Every node must be colored either red or black.
// 2. The root node is black.
// 3. If a node is red, its children must be black.
// 4. Every path from a node to a NULL leaf pointer must contain the same
//    number of black nodes.
//
// Red-black trees tend to perform better than AVL trees in practice because it
// is relatively straightforward to implement some operations in an iterative,
// "top-down" manner. Balancing doesn't need to happen after insertion while
// unwinding some stack, for example.
typedef enum { BLACK, RED } Color;

typedef struct RedBlackTreeNode {
    struct RedBlackTreeNode* left;
    struct RedBlackTreeNode* right;
    int value;
    Color color;
} RedBlackTreeNode;

typedef enum { INORDER, PREORDER, POSTORDER, REVORDER } IterationOrder;

typedef void (*RedBlackTreeYieldFunc)(RedBlackTreeNode* node, int depth);

RedBlackTreeNode* RedBlackTreeCreate(int value);

// Inserts the given value into the tree.
void RedBlackTreeInsert(RedBlackTreeNode** root, int value);

// Removes the node with the given value and returns it. Returns NULL if the
// value is not in the tree.
RedBlackTreeNode* RedBlackTreeRemove(RedBlackTreeNode** root, int value);

// Returns NULL if the value is not in the tree. Otherwise returns the tree
// node containing the given value.
RedBlackTreeNode* RedBlackTreeFind(RedBlackTreeNode* root, int value);

RedBlackTreeNode* RedBlackTreeMin(RedBlackTreeNode* root);

RedBlackTreeNode* RedBlackTreeMax(RedBlackTreeNode* root);

// Traverses the tree, passing each node to the given yieldFunc.
void RedBlackTreeEach(RedBlackTreeNode* root, 
                      IterationOrder order,
                      RedBlackTreeYieldFunc yieldFunc);

#endif
