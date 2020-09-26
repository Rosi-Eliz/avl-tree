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

template <typename T, typename S>
class AVL{
    Node<T, S>* root = nullptr;
    Node<T, S>* insert(vector<pair<T, S>> values);
    int getHeight(Node<T, S>* node) const;
    int getBalance(Node<T, S>* node) const;
    int getMaxHeight(Node<T, S>* node) const;
    Node<T, S>* leftRotation(Node<T, S>* pivotNode);
    Node<T, S>* rightRotation(Node<T, S>* pivotNode);
    Node<T, S>* leftRightRotation(Node<T, S>* pivotNode);
    Node<T, S>* rightleftRotation(Node<T, S>* pivotNode);
    Node<T, S>* rebalance(int balance, Node<T, S> *node);

    Node<T, S>* insert(Node<T, S>* root, pair<T, S> value);
    Node<T, S>* copyNode(Node<T, S>* node, Node<T, S>* nodeToCopy);
    Node<T, S>* deleteNode(Node<T, S>* root, T key);
    Node<T, S>* find(Node<T, S>* node, T key);
    Node<T, S>* smallestValue(Node<T, S>* root);
public:
    AVL();
    AVL(vector<pair<T, S>> elements);
    void operator=(const AVL& tree);
    AVL(const AVL& tree);
    ~AVL();
    void insertElement(const pair<T, S> element);
    Node<T, S>* getRoot() const;
    void print() const;
    void deleteNodeFor(const T key);
};

template <typename T, typename S>
AVL<T, S>::AVL()
{
    root = nullptr;
}

template <typename T, typename S>
AVL<T, S>::AVL(vector<pair<T, S>> elements)
{
    root = insert(elements);
};


template <typename T, typename S>
void recursiveDeletion(Node<T, S>* node)
{
    if(node == nullptr)
        return;
    else
    {
        Node<T, S>* leftChild = node->leftChild;
        Node<T, S>* rightChild = node->rightChild;
        delete node;
        
        recursiveDeletion(leftChild);
        recursiveDeletion(rightChild);
    }
}

template <typename T, typename S>
AVL<T, S>::~AVL<T, S>()
{
    recursiveDeletion(root);
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::copyNode(Node<T, S>* node, Node<T, S>* nodeToCopy)
{
    if(nodeToCopy == nullptr)
    {
        return nullptr;
    }
    else
    {
        node = new Node<T, S>(nodeToCopy->key, nodeToCopy->value);
        
        Node<T, S>* leftChild = nodeToCopy->leftChild;
        Node<T, S>* rightChild = nodeToCopy->rightChild;
        node->leftChild = copyNode(node->leftChild, leftChild);
        node->rightChild = copyNode(node->rightChild, rightChild);
    }
    node->height = nodeToCopy->height;
    return node;
}

template <typename T, typename S>
void AVL<T, S>::operator=(const AVL& tree)
{
    if(this == &tree)
        return;
    
    recursiveDeletion(this->root);
    this->root = copyNode(this->root, tree.root);
};

template <typename T, typename S>
AVL<T, S>::AVL(const AVL& tree)
{
    *this = tree;
};

template <typename T, typename S>
Node<T, S>* find(Node<T, S>* node,T key)
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

template <typename T, typename S>
Node<T, S>* AVL<T, S>::smallestValue(Node<T, S>* root)
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

template <typename T, typename S>
Node<T, S>* AVL<T, S>::deleteNode(Node<T, S>* root, T key)
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
            Node<T, S>* rightChild = root->rightChild;
            delete root;
            root = rightChild;
        }
        else if(root->rightChild == nullptr)
        {
            Node<T, S>* leftChild = root->leftChild;
            delete root;
            root = leftChild;
        }
        else
        {
            Node<T, S>* node = smallestValue(root->rightChild);
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

template <typename T, typename S>
int AVL<T, S>::getHeight(Node<T, S>* node) const
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

template <typename T, typename S>
int AVL<T, S>::getBalance(Node<T, S>* node) const
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

template <typename T, typename S>
int AVL<T, S>::getMaxHeight(Node<T, S>* node) const
{
    return 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::leftRotation(Node<T, S>* pivotNode)
{
    Node<T, S>* pivotRight = pivotNode->rightChild;
    pivotNode->rightChild = pivotRight->leftChild;
    pivotRight->leftChild = pivotNode;
    
    pivotNode->height = getMaxHeight(pivotNode);
    pivotRight->height = getMaxHeight(pivotRight);
    return pivotRight;
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::rightRotation(Node<T, S>* pivotNode)
{
    Node<T, S>* pivotLeft = pivotNode->leftChild;
    pivotNode->leftChild = pivotLeft->rightChild;
    pivotLeft->rightChild = pivotNode;

    pivotNode->height = getMaxHeight(pivotNode);
    pivotLeft->height = getMaxHeight(pivotLeft);
    return pivotLeft;
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::leftRightRotation(Node<T, S>* pivotNode)
{
    pivotNode->leftChild = leftRotation(pivotNode->leftChild);
    pivotNode = rightRotation(pivotNode);
    return pivotNode;
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::rightleftRotation(Node<T, S>* pivotNode)
{
    pivotNode->rightChild = rightRotation(pivotNode->rightChild);
    pivotNode = leftRotation(pivotNode);
    return pivotNode;
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::rebalance(int balance, Node<T, S> *node) {
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

template <typename T, typename S>
Node<T, S>* AVL<T, S>::insert(Node<T, S>* node, pair<T, S> element)
{
    if(node == nullptr)
    {
        return new Node<T, S>(element.first, element.second);
    }
    
    if(element.first > node->key)
    {
        node->rightChild = insert(node->rightChild, element);
    }
    else if(element.first < node->key)
    {
        node->leftChild = insert(node->leftChild, element);
    }
    else
    {
        node->value = element.second;
    }
    node->height = getMaxHeight(node);
    int balance = getBalance(node);
    node = rebalance(balance, node);
    
    return node;
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::insert(vector<pair<T, S>> values)
{
    if(values.empty())
    {
        return nullptr;
    }
    
    if(root == nullptr)
    {
        root = new Node<T, S>(values[0].first, values[0].second);
        values.erase(values.begin());
    }
    
    for(pair<T, S>& element : values)
    {
        root = insert(root, element);
    }
    return root;
}

template <typename T, typename S>
void AVL<T, S>::insertElement(const pair<T, S> element)
{
    root = insert({ element });
}

template <typename T, typename S>
Node<T, S>* AVL<T, S>::getRoot() const
{
    return root;
}

template <typename T, typename S>
void AVL<T, S>::deleteNodeFor(const T key)
{
    root = deleteNode(root, key);
}

template <typename T, typename S>
 void AVL<T, S>::print() const
{
    printTree(root, nullptr, false);
}

#endif /* AVL_h */
