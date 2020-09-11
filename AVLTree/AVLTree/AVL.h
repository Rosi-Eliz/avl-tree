//
//  AVL.h
//  AVLTree
//
//  Created by Rosi-Eliz Dzhurkova on 09.09.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//

#ifndef AVL_h
#define AVL_h

#include "AVLUtilities.h"
#include <vector>

// Rotation threshold
#define THRESHOLD 1

using namespace std;

template <typename T>
class AVL{
    Node<T>* root = nullptr;
    int getHeight(Node<T>* node) const;
    int getBalance(Node<T>* node) const;
    int getMaxHeight(Node<T>* node) const;
    Node<T>* leftRotation(Node<T>* pivotNode);
    Node<T>* rightRotation(Node<T>* pivotNode);
    Node<T>* leftRightRotation(Node<T>* pivotNode);
    Node<T>* rightleftRotation(Node<T>* pivotNode);
    Node<T>* insert(Node<T>* root, const T value);
public:
    Node<T>* insert(const T value);
    Node<T>* insert(vector<T> values);

};

template <typename T>
int AVL<T>::getHeight(Node<T>* node) const
{
    if(node == nullptr)
    {
        return -1;
    }
    else
    {
        return node->height;
    }
}

template <typename T>
int AVL<T>::getBalance(Node<T>* node) const
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

template <typename T>
int AVL<T>::getMaxHeight(Node<T>* node) const
{
    return 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));
}

template <typename T>
Node<T>* AVL<T>::leftRotation(Node<T>* pivotNode)
{
    Node<T>* pivotRight = pivotNode->rightChild;
    pivotNode->rightChild = pivotRight->leftChild;
    pivotRight->leftChild = pivotNode;
    
    pivotNode->height = getMaxHeight(pivotNode);
    pivotRight->height = getMaxHeight(pivotRight);
    return pivotRight;
}

template <typename T>
Node<T>* AVL<T>::rightRotation(Node<T>* pivotNode)
{
    Node<T>* pivotLeft = pivotNode->leftChild;
    pivotNode->leftChild = pivotLeft->rightChild;
    pivotLeft->rightChild = pivotNode;

    pivotNode->height = getMaxHeight(pivotNode);
    pivotLeft->height = getMaxHeight(pivotLeft);
    return pivotLeft;
}

template <typename T>
Node<T>* AVL<T>::leftRightRotation(Node<T>* pivotNode)
{
    pivotNode->leftChild = leftRotation(pivotNode->leftChild);
    pivotNode = rightRotation(pivotNode);
    return pivotNode;
}

template <typename T>
Node<T>* AVL<T>::rightleftRotation(Node<T>* pivotNode)
{
    pivotNode->rightChild = rightRotation(pivotNode->rightChild);
    pivotNode = leftRotation(pivotNode);
    return pivotNode;
}

template <typename T>
Node<T>* AVL<T>::insert(Node<T>* node, const T value)
{
    if(node == nullptr)
    {
        return new Node<T>(value);
    }
    
    if(value > node->value)
    {
        node->rightChild = insert(node->rightChild, value);
    }
    else
    {
        node->leftChild = insert(node->leftChild, value);
    }
    
    node->height = getMaxHeight(node);
    int balance = getBalance(node);
    if(balance < -THRESHOLD)
    {
        if(getBalance(node->leftChild) > 0)
        {
             node = leftRightRotation(node);
        }
        else
        {
            node = rightRotation(node);
        }
    }
    else if(balance > THRESHOLD)
    {
        if(getBalance(node->rightChild) < 0)
        {
            node = rightleftRotation(node);
        }
        else
        {
            node = leftRotation(node);
        }
    }
    return node;
}

template <typename T>
Node<T>* AVL<T>::insert(vector<T> values)
{
    if(values.empty())
        return nullptr;
    
    if(root == nullptr)
    {
        root = new Node<T>(values[0]);
        values.erase(values.begin());
    }
    
    for(T& value : values)
    {
        root = insert(root, value);
    }
    return root;
}

template <typename T>
Node<T>* AVL<T>::insert(const T value)
{
    return insert({value});
}



#endif /* AVL_h */
