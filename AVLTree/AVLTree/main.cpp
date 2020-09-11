//
//  main.cpp
//  AVLTree
//
//  Created by Rosi-Eliz Dzhurkova on 09.09.20.
//  Copyright © 2020 Rosi-Eliz Dzhurkova. All rights reserved.
//

#include <iostream>
#include "AVL.h"
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    
    AVL<int> avl;
    Node<int> *root = avl.insert({14, 17, 11, 7, 53, 4, 13, 12});
    printTree(root, nullptr, false);

    
    return 0;
}
