//
//  AVLUtilities.h
//  AVLTree
//
//  Created by Rosi-Eliz Dzhurkova on 09.09.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//

#ifndef AVLUtilities_h
#define AVLUtilities_h
#include <string>
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    Node* leftChild;
    Node* rightChild;
    T value;
    int height;
    Node(T value, Node* leftChild = nullptr, Node* rightChild = nullptr) : value(value), leftChild(leftChild), rightChild() {
        height = 0;
    }
};

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout<< p->str;
}

template <typename T>
void printTree(Node<T> *root, Trunk *prev, bool isRight)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isRight)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->value << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);
    delete trunk;
}

#endif /* AVLUtilities_h */