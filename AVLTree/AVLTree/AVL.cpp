//
//  AVL.cpp
//  AVLTree
//
//  Created by Rosi-Eliz Dzhurkova on 09.09.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//

#include <stdio.h>
#include "AVL.h"

// Rotation threshold
#define THRESHOLD 1

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
Node<T>* leftRotation(Node<T>* pivotNode)
{
    return nullptr;
}
template <typename T>
Node<T>* rightRotation(Node<T>* pivotNode)
{
    return nullptr;
}
template <typename T>
Node<T>* leftRightRotation(Node<T>* pivotNode)
{
    return nullptr;
}
template <typename T>
Node<T>* rightleftRotation(Node<T>* pivotNode)
{
    return nullptr;
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
        
    }
}

template <typename T>
void AVL<T>::insert(vector<T> values)
{
    if(values.empty())
        return;
    
    if(root == nullptr)
    {
        root = new Node<T>(values[0]);
        erase(values.begin());
    }
    
    for(T& value : values)
    {
        root = insert(root, value);
    }
}

template <typename T>
void AVL<T>::insert(const T value)
{
    insert({value});
}

