//
// Created by roberto on 19/04/15.
//

#ifndef VH2015_TREE_H
#define VH2015_TREE_H

#include "Leaf.h"

template <class T> class Tree{
    pthread_mutex_t* mutexData;
    long* len;
    int* floors;
    long* maximun;
    Leaf* root;
    void split(Leaf*);
    long max(int);
    void createPath(long,int,int*);
    T* searchElementUnlocked(long);
public:
    Tree();
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
template <class T> Tree<T>::Tree(){
    pthread_mutex_t* mutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(mutex,NULL);
    root = static_cast<Leaf*>(malloc(sizeof(Leaf)));
    new(root) Leaf(TREE_SIZE, (int)sizeof(T));
    floors = static_cast<int*>(malloc(sizeof(int)));
    *floors= 1;
    len = static_cast<long*>(malloc(sizeof(int)));
    *len = 0;
    maximun = static_cast<long*>(malloc(sizeof(int)));
    *maximun = max(*floors);
}

/** Destructor
 * @brief: Libera las variables ocupadas
 */
template <class T> Tree<T>::~Tree(){
    free(len);
    free(root);
    free(floors);
    free(maximun);
    free(mutexData);
}

/* Maximo
 * @brief: Realiza un calculo de la maxima cantidad de nodos que puede albergar el arbol con altura X
 */
template <class T> long Tree<T>::max(int floor){
    if(floor > 0){
        return TREE_SIZE + (((floor-1) * floor) / 2) * TREE_SIZE * TREE_SIZE;
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
        for(int i=0; i<TREE_SIZE; i++){
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
    *path = (index)%TREE_SIZE;  //Container
    index=(index-1-max((floor-1)))/TREE_SIZE;
    for(int i=1; i<floor; i++){
        if(index>=TREE_SIZE){
            index=index%TREE_SIZE;
        }
        *(path+i) = index;
        if(i<floor-1){
            index=index/TREE_SIZE;
        }
    }
}

/** Buscador
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido
 */
template <class T> T* Tree<T>::searchElement(long index){
    pthread_mutex_lock(mutexData);
    int floor=*floors;
    if(index <= max(floor)){
        //Localiza el piso
        while(max(floor-1)>index){
            floor--;
        }
        //Crea la ruta
        int* path = static_cast<int*>(malloc(floor * sizeof(int)));
        createPath(index,floor,path);
        //Avanza en la ruta
        Leaf* tmpLeaf = root;
        for(int i=floor-1; i>0; i--){
            tmpLeaf = tmpLeaf->getSons() + *(path+i);
        }
        //Toma el contenedor, es decir el elemento
        T* elementToReturn = static_cast<T*>(tmpLeaf->getContainers() + (*path)*sizeof(T));
        //Libera el espacio de la ruta
        //free(path);
        //retorna el elemento
        pthread_mutex_unlock(mutexData);
        return elementToReturn;
    }else{
        pthread_mutex_unlock(mutexData);
        return 0;
    }
}
template <class T> T* Tree<T>::searchElementUnlocked(long index) {
    int floor=*floors;
    if(index <= max(floor)){
        //Localiza el piso
        while(max(floor-1)>index){
            floor--;
        }
        //Crea la ruta
        int* path = static_cast<int*>(malloc(floor * sizeof(int)));
        createPath(index,floor,path);
        //Avanza en la ruta
        Leaf* tmpLeaf = root;
        for(int i=floor-1; i>0; i--){
            tmpLeaf = tmpLeaf->getSons() + *(path+i);
        }
        //Toma el contenedor, es decir el elemento
        T* elementToReturn = static_cast<T*>(tmpLeaf->getContainers() + (*path)*sizeof(T));
        //Libera el espacio de la ruta
        //free(path);
        //retorna el elemento
        return elementToReturn;
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
    pthread_mutex_lock(mutexData);
    if(index < *maximun){
        T* container = searchElementUnlocked(index);
        new(container) T(param);
        (*len)++;
    }else{
        split(root);
        (*floors)++;
        *maximun = max(*floors);
        insertElement(param,index);
    }
    pthread_mutex_unlock(mutexData);
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
    pthread_mutex_lock(mutexData);
    method(searchElementUnlocked(index),methodParam);
    len--;
    pthread_mutex_unlock(mutexData);
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
    return *maximun;
}


#endif //VH2015_TREE_H