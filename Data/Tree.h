//
// Created by roberto on 19/04/15.
//

#ifndef VH2015_TREE_H
#define VH2015_TREE_H

#include "Leaf.h"
#include <malloc.h>
#include "../Constants.h"
#include "../Models/Subject.h"

template <class T> class Tree{
    int* len;
    int* floors;
    Leaf* root;
    void split(Leaf*);
    int max(int);
    void createPath(int,int,int*);
public:
    Tree();
    ~Tree();
    void* searchElement(int);
    void insertElement(T,int);
    void deleteElement(int);
    void deleteElement(int index, void method(T*));
    int lenght();
    int max();
};

/** Constructor
 * @brief: Reserva el espacio de las variables y la primera hoja
 */
template <class T> Tree<T>::Tree(){

    len = (int*)(malloc(sizeof(int)));
    *len = 0;
    floors = (int*)(malloc(sizeof(int)));
    *floors= 1;
    root = (Leaf*)(malloc(sizeof(Leaf)));
    new(root) Leaf(TREE_SIZE, sizeof(T));
}

/** Destructor
 * @brief: Libera las variables ocupadas
 */
template <class T> Tree<T>::~Tree(){
    free(len);
    free(root);
    free(floors);
}

/* Maximo
 * @brief: Realiza un calculo de la maxima cantidad de nodos que puede albergar el arbol con altura X
 */
template <class T> int Tree<T>::max(int floor){
    if(floor==0){
        return 0;
    }
    int res = TREE_SIZE;
    for(int i = 1; i<floor; i++){
        res += i*(TREE_SIZE)*(TREE_SIZE);
    }
    return res;
}

/** Split
 * @param: Leaf* toSplit
 * @brief: recorre el arbol hasta encontrar una hoja terminal y la divide
 */
template <class T> void Tree<T>::split(Leaf* toSplit){
    if(!(toSplit->isTerminal())){
        void* sons = toSplit->getSons();
        for(int i=0; i<TREE_SIZE; i++){
            split((Leaf*)(sons+i*sizeof(Leaf)));
        };
    }else{
        toSplit->split(TREE_SIZE);
    };
}

/** Crear rutas
 * @param: int index: indice a insertar
 * @param: int floor: piso a ocupar
 * @brief: Realiza los calculos necesarios para generar una serie de enteros con la ruta
 */
template <class T> void Tree<T>::createPath(int index, int floor, int* path){
    *path = (index-1)%TREE_SIZE;  //Container
    index=(index-1-max((floor-1)))/TREE_SIZE;
    for(int i=1; i<floor; i++){
        if(index>=TREE_SIZE){
            index=index%TREE_SIZE;
        }
        *(path+i*sizeof(int)) = index;
        if(i<floor-1){
            index=index/TREE_SIZE;
        }
    }
};

/** Buscador
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido
 */
template <class T> void* Tree<T>::searchElement(int index){
    int floor=*floors;
    if(index <= max(floor)){
        while(max(floor-1)>index){
            floor--;
        }
        int* path = (int*)malloc((floor)*sizeof(int));
        createPath(index,floor,path);
        Leaf* tmp = root;
        for(int i=floor-1; i>0; i--){
            tmp = (Leaf*)(tmp->getSons() + (*(path+i*sizeof(int)))*sizeof(Leaf));
        }
        void* ret = (tmp->getContainers() + (*path)*sizeof(T));
        free(path);
        return ret;
    }else{
        return 0;
    }
}

/** Inserta
 * @param: int index: indice a buscar
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T param, int index){
    if((*len) < max(*floors)){
        void* container = searchElement(index);
        *static_cast<T*>(container) = param;
        (*len)++;
    }else{
        split(root);
        (*floors)++;
        insertElement(param,index);
    }
}

/** Borrador con metodo
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido y lo borra, pero antes ejecuta un metodo sobre el
 */
template <class T> void Tree<T>::deleteElement(int index, void method(T*)){
    index--;
    void* container = searchElement(index);
    method((T*)container);
}

/** Longitud
 * @return int: nodos en uso
 * @brief: devuelve la cantidad de nodos en uso
 */
template <class T> int Tree<T>::lenght(){
    return *len;
}

/** Maximo por piso
 * @return int: maximo numero de nodos
 * @brief: devuelve la cantidad de nodos maxima
 */
template <class T> int Tree<T>::max(){
    return max(*floors);
}


#endif //VH2015_TREE_H