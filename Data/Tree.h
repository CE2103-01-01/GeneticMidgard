//
// Created by roberto on 19/04/15.
//

#ifndef VH2015_TREE_H
#define VH2015_TREE_H

#include "Leaf.h"

template <class T> class Tree{
    long* leafSize;
    long* len;
    long* maximun;
    int* floors;
    Leaf* root;
    void split(Leaf*);
    void createPath(long,int,int*);
    long maximunByFloor(int);
public:
    Tree(long);
    ~Tree();
    T* searchElement(long);
    T* searchAndDo(long, void(T*, void*), void*);
    void insertElement(T,long);
    void insertElement(T);
    void deleteElement(long, void(T*, void*), void*);
    long lenght();
    long max();
};

/** Constructor
 * @brief: Reserva el espacio de las variables y la primera hoja
 */
template <class T> Tree<T>::Tree(long leafSizeParam){
    leafSize = (long*)(malloc(sizeof(long)));
    *leafSize = leafSizeParam;
    maximun = (long*)(malloc(sizeof(long)));
    *maximun = leafSizeParam;
    len = (long*)(malloc(sizeof(long)));
    *len = 0;
    floors = (int*)(malloc(sizeof(int)));
    *floors= 1;
    root = (Leaf*)(malloc(sizeof(Leaf)));
    new(root) Leaf((*leafSize), (int)sizeof(T));
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
template <class T> long Tree<T>::maximunByFloor(int floor){
    if(floor > 0){
        return (*leafSize) + (((floor-1) * floor) / 2) * (*leafSize) * (*leafSize);
    }else{
        return 0;
    }
}

/** Split
 * @param: Leaf* toSplit
 * @brief: recorre el arbol hasta encontrar una hoja terminal y la divide
 */
template <class T> void Tree<T>::split(Leaf* toSplit){
    if(toSplit->getSons()!=0){
        Leaf* sons = toSplit->getSons();
        for(int i=0; i<(*leafSize); i++){
            split(sons+i);
        }
    }else{
        toSplit->split();
    }
}

/** Crear rutas
 * @param: int index: indice a insertar
 * @param: int floor: piso a ocupar
 * @brief: Realiza los calculos necesarios para generar una serie de enteros con la ruta
 */
template <class T> void Tree<T>::createPath(long index, int floor, int* path){
    *path = (index)%(*leafSize);  //Container
    index=(index-maximunByFloor((floor-1)))/(*leafSize);
    for(int i=1; i<floor; i++){
        if(index>=(*leafSize)){
            index=index%(*leafSize);
        }
        *(path+i) = index;
        if(i<floor-1){
            index=index/(*leafSize);
        }
    }
};

/** Buscador
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido
 */
template <class T> T* Tree<T>::searchElement(long index){
    int floor=*floors;
    if(index <= (*maximun)){
        while(maximunByFloor(floor-1)>index){
            floor--;
        }
        int* path = (int*)malloc((floor)*sizeof(int));
        createPath(index,floor,path);
        Leaf* tmp = root;
        for(int i=floor-1; i>0; i--){
            tmp = tmp->getSons() + *(path+i);
        }
        void* ret = (tmp->getContainers() + (*path)*sizeof(T));
        //free(path);
        return static_cast<T*>(ret);
    }else{
        return 0;
    }
}


/** Buscador
 * @param: int index: indice a buscar
 * @param: void method(T*): metodo a ejecutar
 * @param: void* methodParam: parametro del metodo a ejecutar
 * @brief: calcula la ruta al indice recibido
 */
template <class T> T* Tree<T>::searchAndDo(long indexToSearch, void method(T*, void*), void* methodParam){
    T* toReturn = searchElement(indexToSearch);
    method(toReturn, methodParam);
    return toReturn;
}

/** Inserta
 * @param: int index: indice a buscar
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T param, long index){
    if(index < maximunByFloor(*floors)){
        T* container = searchElement(index);
        new(container) T(param);
        (*len)++;
    }else{
        split(root);
        (*floors)++;
        insertElement(param,index);
    }
}

/** Inserta
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T newElement){
    insertElement(newElement,*len);
}

/** Borrador con metodo
 * @param: int index: indice a buscar
 * @param: void method(T*, void*): metodo a ejecutar
 * @param: void* methodParam: parametro del metodo a ejecutar
 * @brief: calcula la ruta al indice recibido y lo borra, pero antes ejecuta un metodo sobre el
 */
template <class T> void Tree<T>::deleteElement(long index, void method(T*, void*), void* methodParam){
    method(searchElement(index),methodParam);
    len--;
}


/** Longitud
 * @return int: nodos en uso
 * @brief: devuelve la cantidad de nodos en uso
 */
template <class T> long Tree<T>::lenght(){
    return *len;
}

/** Maximo por piso
 * @return int: maximo numero de nodos
 * @brief: devuelve la cantidad de nodos maxima
 */
template <class T> long Tree<T>::max(){
    return maximunByFloor(*floors);
}


#endif //VH2015_TREE_H