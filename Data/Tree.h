//
// Created by roberto on 19/04/15.
//

#ifndef PROJECTMIDGARD_TREE_H
#define PROJECTMIDGARD_TREE_H

#include "Leaf.h"

template <class T> class Tree{
    Leaf* root;
    int len;
    int leafSize;
    int floors;
    void split(Leaf*);
    int max(int);
    void createPath(int,int,int*);
public:
    Tree(int);
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
 * @param int leafSizeParam: numero de hijos y nodos por hoja
 */
template <class T> Tree<T>::Tree(int leafSizeParam){
    leafSize = leafSizeParam;
    len = 0;
    floors = 1;
    root = static_cast<Leaf*>(malloc(sizeof(Leaf)));
    new(root) Leaf(sizeof(T), leafSize);
}

/** Destructor
 */
template <class T> Tree<T>::~Tree(){
    free(root);
}

/* Maximo
 * @brief: Realiza un calculo de la maxima cantidad de nodos que puede albergar el arbol con altura X
 */
template <class T> int Tree<T>::max(int floor){
    if(floor > 0){
        return (leafSize) + (((floor-1) * floor) / 2) * (leafSize) * (leafSize);
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
        Leaf* sons = toSplit->getSons();
        for(int i=0; i < leafSize; i++){
            split(sons + i);
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
template <class T> void Tree<T>::createPath(int indexToCreate, int floor, int* path){
    *path = (indexToCreate-1)%(leafSize);  //Container
    indexToCreate=(indexToCreate-1-max((floor-1)))/(leafSize);
    for(int i=1; i<floor; i++){
        if(indexToCreate>=(leafSize)){
            indexToCreate=indexToCreate%(leafSize);
        }
        *(path+i*sizeof(int)) = indexToCreate;
        if(i<floor-1){
            indexToCreate=indexToCreate/(leafSize);
        }
    }
}

/** Buscador
 * @param: int index: indice a buscar
 * @brief: calcula la ruta al indice recibido
 */
template <class T> T* Tree<T>::searchElement(int indexToSearch){
    int dataFloor=floors;
    if(indexToSearch <= max(dataFloor)){
        //Identifica el piso anterior
        while(max(dataFloor-1) > indexToSearch){
            dataFloor--;
        }
        //Crea la ruta
        int* elementPath = static_cast<int*>(malloc((dataFloor)*sizeof(int)));
        createPath(indexToSearch,dataFloor,elementPath);
        //Recorre la ruta
        Leaf* tmpFather = root;
        for(int i=dataFloor-1; i>0; i--){
            tmpFather = tmpFather->getSons() + (*(elementPath+i));
        }
        //Borra la ruta y retorna el dato
        void* element = tmpFather->getContainers() + (*elementPath)*sizeof(T);
        free(elementPath);
        return static_cast<T*>(element);
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
    T* toReturn = searchElement(indexToSearch);
    method(toReturn, methodParam);
    return toReturn;
}

/** Inserta
 * @param: int index: indice a buscar
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T newElement, int index){
    if(len < max(floors)){
        T* container = searchElement(index);
        *container = newElement;
        len++;
    }else{
        split(root);
        floors++;
        insertElement(newElement,index);
    }
}

/** Inserta
 * @param: T param: dato a insertar
 * @brief: calcula la ruta al indice recibido e inserta el dato
 */
template <class T> void Tree<T>::insertElement(T newElement){
    insertElement(newElement,len);
}

/** Borrador con metodo
 * @param: int index: indice a buscar
 * @param: void method(T*, void*): metodo a ejecutar
 * @param: void* methodParam: parametro del metodo a ejecutar
 * @brief: calcula la ruta al indice recibido y lo borra, pero antes ejecuta un metodo sobre el
 */
template <class T> void Tree<T>::deleteElement(int index, void method(T*, void*), void* methodParam){
    method(searchElement(index),methodParam);
    len--;
}

/** Longitud
 * @return int: nodos en uso
 * @brief: devuelve la cantidad de nodos en uso
 */
template <class T> int Tree<T>::lenght(){
    return len;
}

/** Maximo por piso
 * @return int: maximo numero de nodos
 * @brief: devuelve la cantidad de nodos maxima
 */
template <class T> int Tree<T>::max(){
    return max(floors);
}


#endif //PROJECTMIDGARD_TREE_H