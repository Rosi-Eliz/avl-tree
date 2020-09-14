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
    
    AVL<int> avl({14, 17, 11, 7, 53, 4, 13, 12});
//    Node<int> *root = avl.insert({14, 17, 11, 7, 53, 4, 13, 12});
    
    AVL<int> avl2(avl);
    avl.print();

    avl2.deleteNodeFor(53);
    cout<<endl;
    avl2.print();
    
    return 0;
}
