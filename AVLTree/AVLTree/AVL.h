//
//  AVL.h
//  AVLTree
//
//  Created by Rosi-Eliz Dzhurkova on 09.09.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//

#ifndef AVL_h
#define AVL_h

#include <vector>

template<typename T>
struct Node;

using namespace std;

template <typename T>
class AVL{
    Node<T>* root;
    int getHeight(Node<T>* node) const;
    int getBalance(Node<T>* node) const;
    int getMaxHeight(Node<T>* node) const;
    Node<T>* leftRotation(Node<T>* pivotNode);
    Node<T>* rightRotation(Node<T>* pivotNode);
    Node<T>* leftRightRotation(Node<T>* pivotNode);
    Node<T>* rightleftRotation(Node<T>* pivotNode);
    Node<T>* insert(Node<T>* root, const T value);
public:
    AVL();
    void insert(const T value);
    void insert(vector<T> values);

};
#endif /* AVL_h */
