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
    Node<T>* rebalance(int balance, Node<T> *node);

    Node<T>* insert(Node<T>* root, const T value);
    Node<T>* copyNode(Node<T>* node, Node<T>* nodeToCopy);
    Node<T>* deleteNode(Node<T>* root, T key);
    Node<T>* find(Node<T>* node, T key);
    Node<T>* smallestValue(Node<T>* root);
public:
    AVL(vector<T> elements);
    void operator=(const AVL& tree);
    AVL(const AVL& tree);
    ~AVL();
    Node<T>* insert(const T value);
    Node<T>* insert(vector<T> values);
    Node<T>* getRoot() const;
    void print() const;
    void deleteNodeFor(const T key);
};

template <typename T>
AVL<T>::AVL(vector<T> elements)
{
    root = insert(elements);
};


template <typename T>
void recursiveDeletion(Node<T>* node)
{
    if(node == nullptr)
        return;
    else
    {
        Node<T>* leftChild = node->leftChild;
        Node<T>* rightChild = node->rightChild;
        delete node;
        
        recursiveDeletion(leftChild);
        recursiveDeletion(rightChild);
    }
}

template <typename T>
AVL<T>::~AVL<T>()
{
    recursiveDeletion(root);
}

template <typename T>
Node<T>* AVL<T>::copyNode(Node<T>* node, Node<T>* nodeToCopy)
{
    if(nodeToCopy == nullptr)
    {
        return nullptr;
    }
    else
    {
        node = new Node<T>(nodeToCopy->value);
        
        Node<T>* leftChild = nodeToCopy->leftChild;
        Node<T>* rightChild = nodeToCopy->rightChild;
        node->leftChild = copyNode(node->leftChild, leftChild);
        node->rightChild = copyNode(node->rightChild, rightChild);
    }
    node->height = nodeToCopy->height;
    return node;
}

template <typename T>
void AVL<T>::operator=(const AVL& tree)
{
    if(this == &tree)
        return;
    
    recursiveDeletion(this->root);
    this->root = copyNode(this->root, tree.root);
};

template <typename T>
AVL<T>::AVL(const AVL& tree)
{
    *this = tree;
};

template <typename T>
Node<T>* find(Node<T>* node,T key)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    
    else if(node->value == key)
    {
        return node;
    }
    
    else if(key < node->value)
    {
        return find(node->leftChild, key);
    }
    
    else
    {
        return find(node->rightChild, key);
    }
}

template <typename T>
Node<T>* AVL<T>::smallestValue(Node<T>* root)
{
    if(root == nullptr)
    {
        return nullptr;
    }
    if(root->leftChild == nullptr)
    {
        return root;
    }
    return smallestValue(root->leftChild);
}

template <typename T>
Node<T>* AVL<T>::deleteNode(Node<T>* root, T key)
{
    if(root == nullptr)
        return nullptr;
    
    if(key < root->value)
    {
        root->leftChild = deleteNode(root->leftChild, key);
    }
    else if(key > root->value)
    {
        root->rightChild = deleteNode(root->rightChild, key);
    }
    else
    {
        if(root->rightChild == nullptr && root->leftChild == nullptr)
        {
            delete root;
            root = nullptr;
        }
        else if(root->leftChild == nullptr)
        {
            Node<T>* rightChild = root->rightChild;
            delete root;
            root = rightChild;
        }
        else if(root->rightChild == nullptr)
        {
            Node<T>* leftChild = root->leftChild;
            delete root;
            root = leftChild;
        }
        else
        {
            Node<T>* node = smallestValue(root->rightChild);
            if(node == nullptr)
            {
                return root;
            }
            root->value = node->value;
            root->rightChild = deleteNode(root->rightChild, root->value);
        }
    }
    
    if(root == nullptr)
    {
        return root;
    }
    
    //TODO: Re-balancing and height adjustments
    //
    root->height = getMaxHeight(root);
    int newBalance = getBalance(root);
    root = rebalance(newBalance, root);
    
    return root;
}

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
Node<T>* AVL<T>::rebalance(int balance, Node<T> *node) {
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
    node = rebalance(balance, node);
    
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

template <typename T>
Node<T>* AVL<T>::getRoot() const
{
    return root;
}

template <typename T>
void AVL<T>::deleteNodeFor(const T key)
{
    root = deleteNode(root, key);
}

template <typename T>
 void AVL<T>::print() const
{
    printTree(root, nullptr, false);
}

#endif /* AVL_h */
