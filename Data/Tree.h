//
// Created by roberto on 19/04/15.
//

#ifndef VH2015_TREE_H
#define VH2015_TREE_H

#include <cstdlib>
#include <math.h>
#include "Constants.h"
#include "Leaf.h"

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
    T* searchElement(int);
    void insertElement(T,int);
    void insertElement(T);
    void deleteElement(int);
    void deleteElement(int index, void method(T*));
    int lenght();
    int max();
};

/** Constructor
 * @brief: Reserva el espacio de las variables y la primera hoja
 */
template <class T> Tree<T>::Tree(){
    root = static_cast<Leaf*>(malloc(sizeof(Leaf)));
    new(root) Leaf(sizeof(T));
    len = static_cast<int*>(malloc(sizeof(int)));
    *len = 0;
    floors = static_cast<int*>(malloc(sizeof(int)));
    *floors= 1;
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
    if(floor > 0){
        return TREE_SIZE + (((floor-1)*floor)/2) * pow(TREE_SIZE,2);
    }else{
        return 0;
    }
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
        toSplit->split();
    };
}

/** Crear rutas de acceso
 * @param: int indexToInsert: indice a insertar
 * @param: int floor: piso a ocupar
 * @brief: Realiza los calculos necesarios para generar una serie de enteros con la ruta
 */
template <class T> void Tree<T>::createPath(int indexToInsert, int floor, int* path){
    *path = (indexToInsert-1)%TREE_SIZE;  //Container final
    indexToInsert = (indexToInsert-1-max((floor-1)))/TREE_SIZE;
    for(int i=1; i<floor; i++){
        if(indexToInsert>=TREE_SIZE) indexToInsert %= TREE_SIZE;
        *(path + i*sizeof(int)) = indexToInsert;
        if(i<floor-1) indexToInsert /= TREE_SIZE;
    }
};

/** Buscador
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido
 */
template <class T> T* Tree<T>::searchElement(int indexToSearch){
    int dataFloor=*floors;
    if(indexToSearch <= max(dataFloor)){
        while(max(dataFloor-1) > indexToSearch) dataFloor--;
        int* pathToFollow = static_cast<int*>(malloc(dataFloor*sizeof(int)));
        createPath(indexToSearch,dataFloor,pathToFollow);
        Leaf* tmpFather = root;
        for(int i=dataFloor-1; i>0; i--){
            int offset = *(pathToFollow + i*sizeof(int));
            tmpFather = static_cast<Leaf*>(tmpFather->getSons() + offset*sizeof(Leaf));
        }
        free(pathToFollow);
        return static_cast<T*>(tmpFather->getContainers() + (*pathToFollow)*sizeof(T));
    }else{
        return 0;
    }
}

/** Inserta
 * @param: int index: indice a buscar
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T newElement, int index){
    if((*len) < max(*floors)){
        T* container = searchElement(index);
        *container = newElement;
        (*len)++;
    }else{
        split(root);
        (*floors)++;
        insertElement(newElement,index);
    }
}

/** Inserta
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T newElement){
    if((*len) < max(*floors)){
        T* container = searchElement(++(*len));
        *container = newElement;
    }else{
        split(root);
        (*floors)++;
        insertElement(newElement);
    }
}

/** Borrador con metodo
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido y lo borra, pero antes ejecuta un metodo sobre el
 */
template <class T> void Tree<T>::deleteElement(int index, void method(T*)){
    index--;
    method(searchElement(index));
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