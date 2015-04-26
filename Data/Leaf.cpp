//
// Created by roberto on 20/04/15.
//

#include "Leaf.h"

/** @brief crea una hoja con n-1 containers, tal que n=treeSize
 */
Leaf::Leaf(int sizeOfContainerParam){
    sizeOfContainer = static_cast<int*>(malloc(sizeof(int)));
    *sizeOfContainer = sizeOfContainerParam;
    terminal = static_cast<bool*>(malloc(sizeof(bool)));
    *terminal = true;
    containers = malloc((Constants::TREE_SIZE)*sizeOfContainer);
};

/** @brief recorre los containers eliminando cada uno
 */
Leaf::~Leaf(){
    free(terminal);
    free(sons);
    free(containers);
};

/** @brief crea n hojas hijas, tal que n=TREE_SIZE
 */
bool Leaf::isTerminal(){
    return *terminal;
};

/** @brief divide la hoja creando hijos
 */
void Leaf::split(){
    sons = malloc((Constants::TREE_SIZE)*sizeof(Leaf));
    for(int i=0; i<Constants::TREE_SIZE; i++){
        new(static_cast<Leaf*>(sons+i*sizeof(Leaf))) Leaf(*sizeOfContainer);
    }
    *terminal = false;
};

void* Leaf::getSons(){
    return sons;
};

void* Leaf::getContainers(){
    return containers;
};