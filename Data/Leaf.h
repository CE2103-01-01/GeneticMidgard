//
// Created by roberto on 20/04/15.
//

#ifndef PROJECTMIDGARD_LEAF_H
#define PROJECTMIDGARD_LEAF_H

#include <cstdlib>
#include <iostream>
#include "../Constants.h"

/** @brief miembro del arbol
 * Numero de hijos: n, tal que n=treeSize 
 * Numero de containers: n-1
 */
class Leaf{
    int* sizeOfContainer;
    void* containers;
    void* sons;
    bool* terminal;                 //Bandera que indica si es terminal: true=sin hijos
public:
    Leaf(int);
    ~Leaf();
    void* getSons();
    void* getContainers();
    bool isTerminal();
    bool isFull(int);
    void split();
    Leaf* getFather();
    int len();
};

#endif //PROJECTMIDGARD_LEAF_H
