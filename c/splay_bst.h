#ifndef BST_H
#define BST_H

#include "stdbool.h"

// Splay tree containing integers.
//
// Splay trees are similar to AVL trees in that they improve on vanilla BSTs by
// ensuring that sorted inputs don't result in O(n) operations and terrible
// performance. But whereas AVL trees guarantee that no operation takes more
// than O(log n) in the worst case, splay trees only guarantee that the
// amortized complexity will be no more than O(log n), even if an individual
// operation could take as long as O(n).
//
// Splay trees do not need to store height information with each node. They
// also make recently accessed nodes quicker to access. The tree is usually
// rebalanced with each access; the accessed node is rotated to the root. AVL
// trees are only rebalanced on insertion or deletion.
//
// Awesome splay tree visualization: 
// https://www.cs.usfca.edu/~galles/visualization/SplayTree.html
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
