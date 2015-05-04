//
// Created by roberto on 20/04/15.
//

#ifndef PROJECTMIDGARD_LEAF_H
#define PROJECTMIDGARD_LEAF_H

#include <malloc.h>
#include <iostream>

/** @brief miembro del arbol
 * Numero de hijos: n, tal que n=treeSize 
 * Numero de containers: n-1
 */
class Leaf{
    int numberOfSons;
    int sizeOfContainer;
    bool terminal;
    void* containers;
    Leaf* sons;                //Bandera que indica si es terminal: true=sin hijos
public:
    Leaf(int,int);
    ~Leaf();
    Leaf* getSons();
    void* getContainers();
    bool isTerminal();
    void split();
};

#endif //PROJECTMIDGARD_LEAF_H
