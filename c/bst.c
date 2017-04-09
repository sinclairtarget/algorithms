#include <stdlib.h>

#include "bst.h"

bool _BinaryTreeInsert(BinaryTreeNode* node,
                       int value, BinaryTreeNode** ptrToNode);

void _BinaryTreeEach(BinaryTreeNode* node,
                     IterationOrder order,
                     BinaryTreeYieldFunc yieldFunc,
                     int depth);

BinaryTreeNode* BinaryTreeCreate(int value)
{
    BinaryTreeNode* newNode = calloc(1, sizeof(BinaryTreeNode));
    newNode->value = value;
    return newNode;
}

bool BinaryTreeInsert(BinaryTreeNode* node, int value)
{
    return _BinaryTreeInsert(node, value, &node);
}

BinaryTreeNode* BinaryTreeRemove(BinaryTreeNode* node, int value)
{
    // Base case. Value wasn't in the tree.
    if (node == NULL)
        return NULL;

    // Base case. We found our value.
    if (node->value == value) {
        // No children.
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }
        // One left child.
        else if (node->left != NULL && node->right == NULL) {
            BinaryTreeNode* toRet = node->left;
            free(node);
            return toRet;
        }
        // One right child.
        else if (node->left == NULL && node->right != NULL) {
            BinaryTreeNode* toRet = node->right;
            free(node);
            return toRet;
        }
        // Two children.
        else {
            BinaryTreeNode* minRightNode = BinaryTreeMin(node->right);
            node->value = minRightNode->value;
            node->right = BinaryTreeRemove(node->right, minRightNode->value);
            return node;
        }
    }

    // Recursive case. Keep looking.
    if (node->value > value)
        node->left = BinaryTreeRemove(node->left, value);
    else
        node->right = BinaryTreeRemove(node->right, value);

    return node;
}

BinaryTreeNode* BinaryTreeFind(BinaryTreeNode* node, int value)
{
    // Base case. No node. Value was not in the tree.
    if (node == NULL)
        return NULL;

    // Base case. Found our node.
    if (node->value == value)
        return node;

    // Recursive case.
    if (node->value > value)
        return BinaryTreeFind(node->left, value);
    else
        return BinaryTreeFind(node->right, value);
}

BinaryTreeNode* BinaryTreeMin(BinaryTreeNode* node)
{
    BinaryTreeNode* cursor = node;
    while (cursor->left != NULL)
        cursor = cursor->left;

    return cursor;
}

BinaryTreeNode* BinaryTreeMax(BinaryTreeNode* node)
{
    BinaryTreeNode* cursor = node;
    while (cursor->right != NULL)
        cursor = cursor->right;

    return cursor;
}

void BinaryTreeEach(BinaryTreeNode* node, 
                    IterationOrder order,
                    BinaryTreeYieldFunc yieldFunc)
{
    _BinaryTreeEach(node, order, yieldFunc, 0);
}

bool _BinaryTreeInsert(BinaryTreeNode* node,
                       int value,
                       BinaryTreeNode** ptrToNode)
{
    // Base case. Need to insert node here.
    if (node == NULL) {
        BinaryTreeNode* newNode = BinaryTreeCreate(value);
        *ptrToNode = newNode;
        return true;
    }

    // Base case. Found the value; it was already in the tree.
    if (node->value == value)
        return false;

    // Recursive case. Keep searching down the tree.
    if (node->value > value)
        return _BinaryTreeInsert(node->left, value, &node->left);
    else
        return _BinaryTreeInsert(node->right, value, &node->right);
}

void _BinaryTreeEach(BinaryTreeNode* node, 
                     IterationOrder order,
                     BinaryTreeYieldFunc yieldFunc,
                     int depth)
{
    if (node != NULL) {
        switch(order) {
        case INORDER:
            _BinaryTreeEach(node->left, order, yieldFunc, depth + 1);
            yieldFunc(node->value, depth);
            _BinaryTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case PREORDER:
            yieldFunc(node->value, depth);
            _BinaryTreeEach(node->left, order, yieldFunc, depth + 1);
            _BinaryTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case POSTORDER:
            _BinaryTreeEach(node->left, order, yieldFunc, depth + 1);
            _BinaryTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node->value, depth);
            break;
        case REVORDER:
            _BinaryTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node->value, depth);
            _BinaryTreeEach(node->left, order, yieldFunc, depth + 1);
            break;
        }
    }
}
