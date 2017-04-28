#include <stdlib.h>
#include <stdio.h>

#include "splay_bst.h"

SplayTreeNode* _SplayTreeInsert(SplayTreeNode* node,
                                int value, 
                                SplayTreeNode* root,
                                SplayTreeNode** ptrToNode);

SplayTreeNode* _SplayTreeFind(SplayTreeNode* node,
                              int value,
                              SplayTreeNode* root,
                              SplayTreeNode** ptrToNode);

void _SplayTreeEach(SplayTreeNode* node,
                    IterationOrder order,
                    SplayTreeYieldFunc yieldFunc,
                    int depth);

void _Splay(SplayTreeNode* node, 
            SplayTreeNode* accessedNode, 
            SplayTreeNode* root, 
            SplayTreeNode** ptrToNode);

SplayTreeNode* _SplayTreeRotateWithLeftChild(SplayTreeNode* node);
SplayTreeNode* _SplayTreeRotateWithRightChild(SplayTreeNode* node);

SplayTreeNode* SplayTreeCreate(int value)
{
    SplayTreeNode* newNode = calloc(1, sizeof(SplayTreeNode));
    newNode->value = value;
    return newNode;
}

bool SplayTreeInsert(SplayTreeNode** ptrToRoot, int value)
{
    return _SplayTreeInsert(*ptrToRoot, value, *ptrToRoot, ptrToRoot) == NULL;
}

void SplayTreeRemove(SplayTreeNode** ptrToRoot, int value)
{
    SplayTreeNode* foundNode = SplayTreeFind(ptrToRoot, value);
    if (foundNode == NULL) 
        return; // Node with given value not found.

    // Exit early; there's no right subtree to worry about.
    if (foundNode->right == NULL) {
        *ptrToRoot = foundNode->left;
        free(foundNode);
        return;
    }

    // Make the max node in the left subtree the root; it's guaranteed to have
    // no right subtree, so we can attach the right subtree of the found node.
    SplayTreeNode* leftMax = SplayTreeMax(&foundNode->left);
    if (leftMax != NULL) {
        *ptrToRoot = leftMax;
        leftMax->right = foundNode->right;
    }
    else {
        // Oh, hey, actually the left subtree was empty.
        *ptrToRoot = foundNode->right;
    }

    free(foundNode);
}

SplayTreeNode* SplayTreeFind(SplayTreeNode** ptrToRoot, int value)
{
    return _SplayTreeFind(*ptrToRoot, value, *ptrToRoot, ptrToRoot);

}

SplayTreeNode* SplayTreeMax(SplayTreeNode** ptrToRoot)
{
    SplayTreeNode* cursor = *ptrToRoot;
    while (cursor != NULL && cursor->right != NULL)
        cursor = cursor->right;

    return SplayTreeFind(ptrToRoot, cursor->value);
}

SplayTreeNode* SplayTreeMin(SplayTreeNode** ptrToRoot)
{
    SplayTreeNode* cursor = *ptrToRoot;
    while (cursor != NULL && cursor->left != NULL)
        cursor = cursor->left;

    return SplayTreeFind(ptrToRoot, cursor->value);
}

void SplayTreeEach(SplayTreeNode* node, 
                   IterationOrder order,
                   SplayTreeYieldFunc yieldFunc)
{
    _SplayTreeEach(node, order, yieldFunc, 0);
}

SplayTreeNode* _SplayTreeInsert(SplayTreeNode* node,
                                int value,
                                SplayTreeNode* root,
                                SplayTreeNode** ptrToNode)
{
    // Base case. Need to insert node here.
    if (node == NULL) {
        SplayTreeNode* newNode = SplayTreeCreate(value);
        *ptrToNode = newNode;
        return newNode;
    }

    // Base case. Found the value; it was already in the tree.
    if (node->value == value)
        return NULL;

    // Recursive case. Keep searching down the tree.
    SplayTreeNode* newNode;
    if (node->value > value)
        newNode = _SplayTreeInsert(node->left, value, root, &node->left);
    else
        newNode = _SplayTreeInsert(node->right, value, root, &node->right);

    _Splay(node, newNode, root, ptrToNode);
    return newNode;
}

SplayTreeNode* _SplayTreeFind(SplayTreeNode* node,
                              int value,
                              SplayTreeNode* root,
                              SplayTreeNode** ptrToNode)
{
    // Base case. No node. Value was not in the tree.
    if (node == NULL)
        return NULL;

    // Base case. Found our node.
    if (node->value == value)
        return node;

    // Recursive case.
    SplayTreeNode* foundNode;
    if (node->value > value)
        foundNode = _SplayTreeFind(node->left, value, root, &node->left);
    else
        foundNode = _SplayTreeFind(node->right, value, root, &node->right);

    _Splay(node, foundNode, root, ptrToNode);
    return foundNode;
}

void _SplayTreeEach(SplayTreeNode* node, 
                    IterationOrder order,
                    SplayTreeYieldFunc yieldFunc,
                    int depth)
{
    if (node != NULL) {
        switch (order) {
        case INORDER:
            _SplayTreeEach(node->left, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            _SplayTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case PREORDER:
            yieldFunc(node, depth);
            _SplayTreeEach(node->left, order, yieldFunc, depth + 1);
            _SplayTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case POSTORDER:
            _SplayTreeEach(node->left, order, yieldFunc, depth + 1);
            _SplayTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            break;
        case REVORDER:
            _SplayTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            _SplayTreeEach(node->left, order, yieldFunc, depth + 1);
            break;
        }
    }
}

void _Splay(SplayTreeNode* node, 
            SplayTreeNode* accessedNode,
            SplayTreeNode* root,
            SplayTreeNode** ptrToNode)
{
    // No node accessed; no splaying to do be done.
    if (accessedNode == NULL) return;

    // Accessed node is one below root; rotate once.
    if (node == root && node->left == accessedNode) {
        printf("Rotate left at root.\n");
        *ptrToNode = _SplayTreeRotateWithLeftChild(node);
        return;
    }
    else if (node == root && node->right == accessedNode) {
        printf("Rotate right at root.\n");
        *ptrToNode = _SplayTreeRotateWithRightChild(node);
        return;
    }

    SplayTreeNode* leftChild = node->left;
    SplayTreeNode* rightChild = node->right;

    // Zig-Zag case left.
    if (leftChild != NULL && leftChild->right == accessedNode) {
        printf("Zig-Zag case left.\n");
        node->left = _SplayTreeRotateWithRightChild(leftChild);
        *ptrToNode = _SplayTreeRotateWithLeftChild(node);
    }

    // Zig-Zag case right.
    if (rightChild != NULL && rightChild->left == accessedNode) {
        printf("Zig-Zag case right.\n");
        node->right = _SplayTreeRotateWithLeftChild(rightChild);
        *ptrToNode = _SplayTreeRotateWithRightChild(node);
    }

    // Zig-Zig case left.
    if (leftChild != NULL && leftChild->left == accessedNode) {
        printf("Zig-Zig case left.\n");
        node->left = leftChild->right;
        leftChild->right = node;
        leftChild->left = accessedNode->right;
        accessedNode->right = leftChild;
        *ptrToNode = accessedNode;
    }

    // Zig-Zig case right.
    if (rightChild != NULL && rightChild->right == accessedNode) {
        printf("Zig-Zig case right.\n");
        node->right = rightChild->left;
        rightChild->left = node;
        rightChild->right = accessedNode->left;
        accessedNode->left = rightChild;
        *ptrToNode = accessedNode;
    }

    printf("\n");
}

SplayTreeNode* _SplayTreeRotateWithLeftChild(SplayTreeNode* node)
{
    SplayTreeNode* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    return leftChild;
}

SplayTreeNode* _SplayTreeRotateWithRightChild(SplayTreeNode* node)
{
    SplayTreeNode* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    return rightChild;
}
