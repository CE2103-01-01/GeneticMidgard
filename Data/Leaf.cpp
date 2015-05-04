//
// Created by roberto on 20/04/15.
//

#include "Leaf.h"

/** @brief crea una hoja con n-1 containers, tal que n=treeSize
 */
Leaf::Leaf(int sizeOfContainerParam, int numberOfSonsParam){
    numberOfSons = numberOfSonsParam;
    sizeOfContainer = sizeOfContainerParam;
    terminal = true;
    containers = malloc(sizeOfContainer * numberOfSons);
    sons = static_cast<Leaf*>(malloc(numberOfSons * sizeof(Leaf)));
}

/** @brief recorre los containers eliminando cada uno
 */
Leaf::~Leaf(){
    free(sons);
    free(containers);
}

/** @brief crea n hojas hijas, tal que n=(*(*numberOfSons))
 */
bool Leaf::isTerminal(){
    return terminal;
}

/** @brief divide la hoja creando hijos
 */
void Leaf::split(){
    for(int i=0; i<(numberOfSons); i++){
        new(sons+i) Leaf(sizeOfContainer, numberOfSons);
    }
    terminal = false;
}

/** @brief devuelve los hijos
 */
Leaf* Leaf::getSons(){
    return sons;
}

/** @brief devuelve los datos
 */
void* Leaf::getContainers(){
    return containers;
}