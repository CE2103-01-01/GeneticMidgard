//
// Created by roberto on 20/04/15.
//

#include "Leaf.h"

/** @brief crea una hoja con n-1 containers, tal que n=treeSize
 */
Leaf::Leaf(int sizeOfContainerParam, int* numberOfSonsParam){
    numberOfSons = numberOfSonsParam;
    sizeOfContainer = static_cast<int*>(malloc(sizeof(int)));
    *sizeOfContainer = sizeOfContainerParam;
    terminal = static_cast<int*>(malloc(sizeof(int)));
    *terminal = 1;
    containers = malloc((*sizeOfContainer) * (*numberOfSons));
    sons = 0;
}

/** @brief recorre los containers eliminando cada uno
 */
Leaf::~Leaf(){
}

/** @brief crea n hojas hijas, tal que n=(*(*numberOfSons))
 */
int Leaf::isTerminal(){
    return (*terminal);
}

/** @brief divide la hoja creando hijos
 */
void Leaf::split(){
    sons = malloc((*numberOfSons) * sizeof(Leaf));
    for(int i=0; i<((*numberOfSons)); i++){
        new(static_cast<Leaf*>(sons + i*sizeof(Leaf))) Leaf(*sizeOfContainer, numberOfSons);
    }
    *terminal = 0;
}

/** @brief devuelve los hijos
 */
void* Leaf::getSons(){
    return sons;
}

/** @brief devuelve los datos
 */
void* Leaf::getContainers(){
    return containers;
}