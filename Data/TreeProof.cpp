//
// Created by roberto on 26/04/15.
//

#include "TreeProof.h"

void print(int* toPrint, void* position){
    std::cout << *static_cast<int*>(position) << " : " << *toPrint <<std::endl;
}

void setNumber(int* toSet, void* number){
    *toSet = *static_cast<int*>(number);
}

void treeProof(){
    Tree<int>* tree = static_cast<Tree<int>*>(malloc(sizeof(Tree<int>)));
    new(tree) Tree<int>(TREE_SIZE);
    std::cout << "SE CREA EL ARBOL" <<std::endl;
    std::cout << "SE INSERTARAN LOS ELEMENTOS MEDIANTE AMBOS METODOS" <<std::endl;
    std::cin.get();
    for(int i=0; i<10000; i++){
        tree->insertElement(i);
    }
    std::cout << "SE IMPRIMIRAN MEDIANTE METODO COUT" <<std::endl;
    std::cin.get();
    for(int i=0; i<10000; i++){
        std::cout << *(tree->searchElement(i)) <<std::endl;
    }
    std::cout << "SE IMPRIMIRAN MEDIANTE METODO POR PARAMETRO" <<std::endl;
    std::cin.get();
    for(int i=0; i<10000; i++){
        tree->searchAndDo(i,print,static_cast<void*>(&i));
    }
    std::cout << "SE COLOCARAN EN 9 LOS NUMEROS EXITOSAMENTE" <<std::endl;
    std::cin.get();
    void* nine = malloc(sizeof(int));
    *static_cast<int*>(nine) = 9;
    for(int i=0; i<10000; i++){
        tree->searchAndDo(i,setNumber,nine);
    }
    free(nine);
    std::cout << "SE IMPRIMIRAN MEDIANTE METODO POR PARAMETRO" <<std::endl;
    std::cin.get();
    for(int i=0; i<10000; i++){
        tree->searchAndDo(i,print,static_cast<void*>(&i));
    }
}