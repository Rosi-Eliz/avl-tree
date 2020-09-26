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
    
    AVL<int, char> avl({pair<int, char>(14, 'A'),
        pair<int, char>(17, 'B'),
        pair<int, char>(11, 'C'),
        pair<int, char>(7, 'D'),
        pair<int, char>(53, 'E'),
        pair<int, char>(4, 'F'),
        pair<int, char>(13, 'G'),
        pair<int, char>(12, 'H')});
    
    AVL<int, char> avl2(avl);
    avl.print();
    
    return 0;
}
