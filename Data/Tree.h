//
// Created by roberto on 19/04/15.
//

#ifndef VH2015_TREE_H
#define VH2015_TREE_H

#include "Leaf.h"

template <class T> class Tree{
    pthread_mutex_t* mutex;
    int* len;
    int* floors;
    Leaf* root;
    void split(Leaf*);
    int max(int);
    void createPath(int,int,int*);
    T* searchElementUnlocked(int);
public:
    Tree();
    ~Tree();
    T* searchElement(int);
    T* searchAndDo(int, void(T*, void*), void*);
    void insertElement(T,int);
    void insertElement(T);
    void deleteElement(int, void(T*, void*), void*);
    int lenght();
    int max();
};

/** Constructor
 * @brief: Reserva el espacio de las variables y la primera hoja
 */
template <class T> Tree<T>::Tree(){
    root = (Leaf*)(malloc(sizeof(Leaf)));
    new(root) Leaf(TREE_SIZE, (int)sizeof(T));
    len = (int*)(malloc(sizeof(int)));
    *len = 0;
    floors = (int*)(malloc(sizeof(int)));
    *floors= 1;
    pthread_mutex_t* mutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(mutex,NULL);
}

/** Destructor
 * @brief: Libera las variables ocupadas
 */
template <class T> Tree<T>::~Tree(){
    pthread_mutex_lock( &mutexData );
    free(len);
    free(root);
    free(floors);
    pthread_mutex_unlock( &mutexData );
    free(mutex);
}

/* Maximo
 * @brief: Realiza un calculo de la maxima cantidad de nodos que puede albergar el arbol con altura X
 */
template <class T> int Tree<T>::max(int floor){
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
        };
    }else{
        toSplit->split();
    };
}

/** Crear rutas
 * @param: int index: indice a insertar
 * @param: int floor: piso a ocupar
 * @brief: Realiza los calculos necesarios para generar una serie de enteros con la ruta
 */
template <class T> void Tree<T>::createPath(int index, int floor, int* path){
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
};

/** Buscador
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido
 */
template <class T> T* Tree<T>::searchElement(int index){
    pthread_mutex_lock(mutex);
    int floor=*floors;
    if(index <= max(floor)){
        while(max(floor-1)>index){
            floor--;
        }
        int* path = (int*)malloc((floor)*sizeof(int));
        createPath(index,floor,path);
        Leaf* tmp = root;
        for(int i=floor-1; i>0; i--){
            tmp = tmp->getSons() + *(path+i);
        }
        void* ret = (tmp->getContainers() + (*path)*sizeof(T));
        pthread_mutex_unlock(mutex);
       return static_cast<T*>(ret);
    }else{
        pthread_mutex_unlock(mutex);
        return 0;
    }

}
template <class T> T* Tree<T>::searchElementUnlocked(int index){
    int floor=*floors;
    if(index <= max(floor)){
        while(max(floor-1)>index){
            floor--;
        }
        int* path = (int*)malloc((floor)*sizeof(int));
        createPath(index,floor,path);
        Leaf* tmp = root;
        for(int i=floor-1; i>0; i--){
            tmp = tmp->getSons() + *(path+i);
        }
        void* ret = (tmp->getContainers() + (*path)*sizeof(T));
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
template <class T> T* Tree<T>::searchAndDo(int indexToSearch, void method(T*, void*), void* methodParam){
    pthread_mutex_lock( mutex );
    T* toReturn = searchElementUnlocked(indexToSearch);
    method(toReturn, methodParam);
    pthread_mutex_unlock(mutex);
    return toReturn;
}

/** Inserta
 * @param: int index: indice a buscar
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T param, int index){
    pthread_mutex_lock(mutex);
    if(index < max(*floors)){
        T* container = searchElementUnlocked(index);
        new(container) T(param);
        (*len)++;
        pthread_mutex_unlock(mutex);
    }else{
        split(root);
        (*floors)++;
        pthread_mutex_unlock(mutex);
        insertElement(param,index);
    }
    pthread_mutex_unlock(mutex);
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
template <class T> void Tree<T>::deleteElement(int index, void method(T*, void*), void* methodParam){
    pthread_mutex_lock(mutex);
    method(searchElementUnlocked(index),methodParam);
    len--;
    pthread_mutex_unlock(mutex);
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