//
// Created by roberto on 26/04/15.
//

#include "TreeProof.h"

void print(int* toPrint){
    std::cout << *toPrint <<std::endl;
}

void setCero(int* toSetCero){
    *toSetCero = 0;
}

void proof(){
    Tree<int>* tree = static_cast<Tree<int>*>(malloc(sizeof(Tree<int>)));
    new(tree) Tree<int>();
    std::cout << "SE CREA EL ARBOL" <<std::endl;
    std::cout << "SE INSERTARAN LOS ELEMENTOS" <<std::endl;
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
        tree->searchAndDo(i,print);
    }
    std::cout << "SE COLOCARAN EN 0 LOS NUMEROS EXITOSAMENTE" <<std::endl;
    std::cin.get();
    for(int i=0; i<10000; i++){
        tree->searchAndDo(i,setCero);
    }
    std::cout << "SE IMPRIMIRAN MEDIANTE METODO POR PARAMETRO" <<std::endl;
    std::cin.get();
    for(int i=0; i<10000; i++){
        tree->searchAndDo(i,print);
    }
}