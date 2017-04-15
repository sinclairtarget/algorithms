#include <stdlib.h>
#include <stdio.h>

#include "avl_bst.h"

#define max(a, b) ((b) > (a) ? (b) : (a))
#define AVL_MAX_ALLOWED_IMBALANCE 1

void _AVLTreeEach(AVLTreeNode* node,
                  IterationOrder order,
                  AVLTreeYieldFunc yieldFunc,
                  int depth);

char _AVLTreeHeight(AVLTreeNode* node);
AVLTreeNode* _AVLTreeBalance(AVLTreeNode* node);

AVLTreeNode* _AVLTreeRotateWithLeftChild(AVLTreeNode* node);
AVLTreeNode* _AVLTreeRotateWithRightChild(AVLTreeNode* node);

AVLTreeNode* _AVLTreeDoubleRotateWithLeftChild(AVLTreeNode* node);
AVLTreeNode* _AVLTreeDoubleRotateWithRightChild(AVLTreeNode* node);

AVLTreeNode* AVLTreeCreate(int value)
{
    AVLTreeNode* newNode = calloc(1, sizeof(AVLTreeNode));
    newNode->value = value;
    return newNode;
}

AVLTreeNode* AVLTreeInsert(AVLTreeNode* node, int value)
{
    // Base case. Need to insert node here.
    if (node == NULL)
        return AVLTreeCreate(value);

    // Base case. Found the value; it was already in the tree.
    if (node->value == value)
        return node;

    // Recursive case. Keep searching down the tree.
    if (node->value > value)
        node->left = AVLTreeInsert(node->left, value);
    else
        node->right = AVLTreeInsert(node->right, value);

    return _AVLTreeBalance(node);
}

AVLTreeNode* AVLTreeRemove(AVLTreeNode* node, int value)
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
            AVLTreeNode* toRet = node->left;
            free(node);
            return toRet;
        }
        // One right child.
        else if (node->left == NULL && node->right != NULL) {
            AVLTreeNode* toRet = node->right;
            free(node);
            return toRet;
        }
        // Two children.
        else {
            AVLTreeNode* minRightNode = AVLTreeMin(node->right);
            node->value = minRightNode->value;
            node->right = AVLTreeRemove(node->right, minRightNode->value);
            return node;
        }
    }

    // Recursive case. Keep looking.
    if (node->value > value)
        node->left = AVLTreeRemove(node->left, value);
    else
        node->right = AVLTreeRemove(node->right, value);

    return _AVLTreeBalance(node);
}

AVLTreeNode* AVLTreeFind(AVLTreeNode* node, int value)
{
    // Base case. No node. Value was not in the tree.
    if (node == NULL)
        return NULL;

    // Base case. Found our node.
    if (node->value == value)
        return node;

    // Recursive case.
    if (node->value > value)
        return AVLTreeFind(node->left, value);
    else
        return AVLTreeFind(node->right, value);
}

AVLTreeNode* AVLTreeMin(AVLTreeNode* node)
{
    AVLTreeNode* cursor = node;
    while (cursor->left != NULL)
        cursor = cursor->left;

    return cursor;
}

AVLTreeNode* AVLTreeMax(AVLTreeNode* node)
{
    AVLTreeNode* cursor = node;
    while (cursor->right != NULL)
        cursor = cursor->right;

    return cursor;
}

void AVLTreeEach(AVLTreeNode* node, 
                 IterationOrder order,
                 AVLTreeYieldFunc yieldFunc)
{
    _AVLTreeEach(node, order, yieldFunc, 0);
}

void _AVLTreeEach(AVLTreeNode* node, 
                  IterationOrder order,
                  AVLTreeYieldFunc yieldFunc,
                  int depth)
{
    if (node != NULL) {
        switch(order) {
        case INORDER:
            _AVLTreeEach(node->left, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            _AVLTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case PREORDER:
            yieldFunc(node, depth);
            _AVLTreeEach(node->left, order, yieldFunc, depth + 1);
            _AVLTreeEach(node->right, order, yieldFunc, depth + 1);
            break;
        case POSTORDER:
            _AVLTreeEach(node->left, order, yieldFunc, depth + 1);
            _AVLTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            break;
        case REVORDER:
            _AVLTreeEach(node->right, order, yieldFunc, depth + 1);
            yieldFunc(node, depth);
            _AVLTreeEach(node->left, order, yieldFunc, depth + 1);
            break;
        }
    }
}

char _AVLTreeHeight(AVLTreeNode* node)
{
    return node == NULL ? -1 : node->height;
}

AVLTreeNode* _AVLTreeBalance(AVLTreeNode* node)
{
    char heightLeft = _AVLTreeHeight(node->left);
    char heightRight = _AVLTreeHeight(node->right);

    // AVL tree balance condition is that left and right height cannot differ
    // by more than one.

    // If left height is too great:
    //   If left grandchild height is greater than right:
    //     Outer insertion, single rotation 
    //   Else
    //     Inner insertion, double rotation
    // Else if right height is too great:
    //   If right grandchild height is greater than left:
    //     Outer insertion, single rotation
    //   Else
    //     Inner insertion, double rotation
    // else if right height is too great:
    if (heightLeft - heightRight > AVL_MAX_ALLOWED_IMBALANCE) {
        char heightLeftOuter = _AVLTreeHeight(node->left->left);
        char heightLeftInner = _AVLTreeHeight(node->left->right);

        if (heightLeftOuter > heightLeftInner) {
            node = _AVLTreeRotateWithLeftChild(node);
        }
        else {
            node = _AVLTreeDoubleRotateWithLeftChild(node);
        }
    }
    else if (heightRight - heightLeft > AVL_MAX_ALLOWED_IMBALANCE) {
        char heightRightOuter = _AVLTreeHeight(node->right->right);
        char heightRightInner = _AVLTreeHeight(node->right->left);

        if (heightRightOuter > heightRightInner) {
            node = _AVLTreeRotateWithRightChild(node);
        }
        else {
            node = _AVLTreeDoubleRotateWithRightChild(node);
        }
    }

    node->height = max(_AVLTreeHeight(node->left),
                       _AVLTreeHeight(node->right)) + 1;
    return node;
}

AVLTreeNode* _AVLTreeRotateWithLeftChild(AVLTreeNode* node)
{
    AVLTreeNode* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    node->height = max(_AVLTreeHeight(node->left),
                       _AVLTreeHeight(node->right)) + 1;
    leftChild->height = max(_AVLTreeHeight(leftChild->left),
                            _AVLTreeHeight(leftChild->right)) + 1;

    return leftChild;
}

AVLTreeNode* _AVLTreeRotateWithRightChild(AVLTreeNode* node)
{
    AVLTreeNode* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    node->height = max(_AVLTreeHeight(node->left),
                       _AVLTreeHeight(node->right)) + 1;
    rightChild->height = max(_AVLTreeHeight(rightChild->left),
                             _AVLTreeHeight(rightChild->right)) + 1;

    return rightChild;
}

AVLTreeNode* _AVLTreeDoubleRotateWithLeftChild(AVLTreeNode* node)
{
    node->left = _AVLTreeRotateWithRightChild(node->left);
    return _AVLTreeRotateWithLeftChild(node);
}

AVLTreeNode* _AVLTreeDoubleRotateWithRightChild(AVLTreeNode* node)
{
    node->right = _AVLTreeRotateWithLeftChild(node->right);
    return _AVLTreeRotateWithRightChild(node);
}
