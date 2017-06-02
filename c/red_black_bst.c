#include <stdlib.h>
#include <stdio.h>

#include "red_black_bst.h"

#define max(a, b) ((b) > (a) ? (b) : (a))

void _RedBlackTreeEach(RedBlackTreeNode* node,
                       IterationOrder order,
                       RedBlackTreeYieldFunc yieldFunc,
                       int depth);

void _RedBlackTreeBalance(RedBlackTreeNode* current,
                          RedBlackTreeNode* parent,
                          RedBlackTreeNode* grand,
                          RedBlackTreeNode** grandPtr,
                          RedBlackTreeNode** root);

RedBlackTreeNode* _RedBlackTreeRotateWithLeftChild(RedBlackTreeNode* node);
RedBlackTreeNode* _RedBlackTreeRotateWithRightChild(RedBlackTreeNode* node);

RedBlackTreeNode* _RedBlackTreeDoubleRotateWithLeftChild(RedBlackTreeNode* node);
RedBlackTreeNode* _RedBlackTreeDoubleRotateWithRightChild(RedBlackTreeNode* node);

Color _Color(RedBlackTreeNode* node);

RedBlackTreeNode* _ColorRed(RedBlackTreeNode* current,
                            RedBlackTreeNode* sibling,
                            RedBlackTreeNode* parent,
                            RedBlackTreeNode** parentPtr);

RedBlackTreeNode* RedBlackTreeCreate(int value)
{
    RedBlackTreeNode* newNode = calloc(1, sizeof(RedBlackTreeNode));
    newNode->value = value;
    newNode->color = BLACK;
    return newNode;
}

void RedBlackTreeInsert(RedBlackTreeNode** root, int value)
{
    RedBlackTreeNode** current = root;
    RedBlackTreeNode** parent = root;
    RedBlackTreeNode** grand = root;    // grandparent

    while (*current != NULL && (*current)->value != value) {
        if (_Color((*current)->left) == RED && _Color((*current)->right) == RED)
            _RedBlackTreeBalance(*current, *parent, *grand, grand, root);

        grand = parent; parent = current;
        current = (value < (*current)->value) ?
                    &(*current)->left : &(*current)->right;
    }

    if (*current != NULL) return; // value already exists (at current)

    *current = RedBlackTreeCreate(value);
    _RedBlackTreeBalance(*current, *parent, *grand, grand, root);
}

RedBlackTreeNode* RedBlackTreeRemove(RedBlackTreeNode** root, int value)
{
    RedBlackTreeNode** current = root;
    RedBlackTreeNode** sibling = root;
    RedBlackTreeNode** parent = root;

    (*root)->color = RED;

    while (*current != NULL && (*current)->value != value) {
        parent = current;
        current = (value < (*current)->value) ?
                    &(*current)->left : &(*current)->right;
        sibling = (value < (*sibling)->value) ?
                    &(*sibling)->right : &(*sibling)->left;

        if ((*current)->color == BLACK)
            _ColorRed(*current, *sibling, *parent, parent);
    }

    if (*current == NULL) return NULL; // Value not in tree

    RedBlackTreeNode* deletedNode;

    // Leaf node case. Just delete.
    if ((*current)->left == NULL && (*current)->right == NULL) {
        deletedNode = *current;
        *current = NULL;
    }
    // Only left child. Replace with largest node in left subtree.
    else if ((*current)->right == NULL) {
        int val = RedBlackTreeMax((*current)->left)->value;
        deletedNode = RedBlackTreeRemove(&(*current)->left, val);
        deletedNode->value = (*current)->value;
        (*current)->value = val;
    }
    // Right child. Replace with smallest node in right subtree.
    else {
        int val = RedBlackTreeMin((*current)->right)->value;
        deletedNode = RedBlackTreeRemove(&(*current)->right, val);
        deletedNode->value = (*current)->value;
        (*current)->value = val;
    }

    if (*root != NULL) (*root)->color = BLACK;
    return deletedNode;
}

RedBlackTreeNode* RedBlackTreeFind(RedBlackTreeNode* node, int value)
{
    // Base case. No node. Value was not in the tree.
    if (node == NULL)
        return NULL;

    // Base case. Found our node.
    if (node->value == value)
        return node;

    // Recursive case.
    if (node->value > value)
        return RedBlackTreeFind(node->left, value);
    else
        return RedBlackTreeFind(node->right, value);
}

RedBlackTreeNode* RedBlackTreeMin(RedBlackTreeNode* node)
{
    RedBlackTreeNode* cursor = node;
    while (cursor->left != NULL)
        cursor = cursor->left;

    return cursor;
}

RedBlackTreeNode* RedBlackTreeMax(RedBlackTreeNode* node)
{
    RedBlackTreeNode* cursor = node;
    while (cursor->right != NULL)
        cursor = cursor->right;

    return cursor;
}

void RedBlackTreeEach(RedBlackTreeNode* node,
                      IterationOrder order,
                      RedBlackTreeYieldFunc yieldFunc)
{
    _RedBlackTreeEach(node, order, yieldFunc, 0);
}

void _RedBlackTreeEach(RedBlackTreeNode* node,
                       IterationOrder order,
                       RedBlackTreeYieldFunc yieldFunc,
                       int depth)
{
    if (node != NULL) {
        switch(order) {
        case INORDER:
            _RedBlackTreeEach(node->left, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            _RedBlackTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case PREORDER:
            yieldFunc(node, depth);
            _RedBlackTreeEach(node->left, order, yieldFunc, depth + 1);
            _RedBlackTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case POSTORDER:
            _RedBlackTreeEach(node->left, order, yieldFunc, depth + 1);
            _RedBlackTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            break;
        case REVORDER:
            _RedBlackTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            _RedBlackTreeEach(node->left, order, yieldFunc, depth + 1);
            break;
        }
    }
}

void _RedBlackTreeBalance(RedBlackTreeNode* current,
                          RedBlackTreeNode* parent,
                          RedBlackTreeNode* grand,
                          RedBlackTreeNode** grandPtr,
                          RedBlackTreeNode** root)
{
    current->color = RED;

    if (current->left != NULL && current->right != NULL) {
        current->left->color = BLACK;
        current->right->color = BLACK;
    }

    if (parent->color == RED) {
        // Two consecutive reds, so we need to rotate.
        // Single rotation cases:
        if (current == parent->left && parent == grand->left)
            *grandPtr = _RedBlackTreeRotateWithLeftChild(grand);
        else if (current == parent->right && parent == grand->right)
            *grandPtr = _RedBlackTreeRotateWithRightChild(grand);
        // Double rotation cases:
        else if (current == parent->right && parent == grand->left)
            *grandPtr = _RedBlackTreeDoubleRotateWithLeftChild(grand);
        else if (current == parent->left && parent == grand->right)
            *grandPtr = _RedBlackTreeDoubleRotateWithRightChild(grand);
    }

    (*root)->color = BLACK;
}

RedBlackTreeNode* _RedBlackTreeRotateWithLeftChild(RedBlackTreeNode* node)
{
    RedBlackTreeNode* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    node->color = RED;
    leftChild->color = BLACK;

    return leftChild;
}

RedBlackTreeNode* _RedBlackTreeRotateWithRightChild(RedBlackTreeNode* node)
{
    RedBlackTreeNode* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    node->color = RED;
    rightChild->color = BLACK;

    return rightChild;
}

RedBlackTreeNode* _RedBlackTreeDoubleRotateWithLeftChild(RedBlackTreeNode* node)
{
    node->left = _RedBlackTreeRotateWithRightChild(node->left);
    return _RedBlackTreeRotateWithLeftChild(node);
}

RedBlackTreeNode* _RedBlackTreeDoubleRotateWithRightChild(RedBlackTreeNode* node)
{
    node->right = _RedBlackTreeRotateWithLeftChild(node->right);
    return _RedBlackTreeRotateWithRightChild(node);
}

Color _Color(RedBlackTreeNode* node)
{
    if (node == NULL) return BLACK;
    return node->color;
}

RedBlackTreeNode* _ColorRed(RedBlackTreeNode* current,
                            RedBlackTreeNode* sibling,
                            RedBlackTreeNode* parent,
                            RedBlackTreeNode** parentPtr)
{
    RedBlackTreeNode* newParent = parent;

    // If the parent is black, then we have a special case.
    // Rotate with the sibling.

    // If both children of current are black...
    if (_Color(current->left) == BLACK && _Color(current->right) == BLACK) {
        // If sibling's children are also black, just flip colors.
        if (_Color(sibling->left) == BLACK &&
            _Color(sibling->right) == BLACK) {
            current->color = RED;
            sibling->color = RED;
        }
        // Else sibling has at least one red child.
        // If the current node is the parent's left child...
        else if (parent->left == current) {
            // If the sibling's left child is the red one, double rotate.
            // Otherwise it's the right child (or both), single rotate.
        }
        // Otherwise the current node is the parent's right child...
        else {
            // If the sibling's left child is the red one, double rotate.
            // Otherwise it's the right child (or both), single rotate.
        }
    }

    return newParent;
}
