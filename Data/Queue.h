//
// Created by pablo on 22/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_QUEUE_H
#define PROJECTMIDGARDLOGIC_QUEUE_H

#include <malloc.h>

template<class T>class NodeQueue;
template<class T>
class Queue {
private:
    pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
    NodeQueue<T>* _head;
    unsigned int lenght;
    void pushNode(NodeQueue<T>*);
public:
    void push(T*);
    void push(T);
    void pop();
    bool empty();
    int size();

    T top();
};

template<class T>
class NodeQueue
{
    friend class Queue<T>;

private:
    T* data;
    NodeQueue<T> *next;
public:
    NodeQueue(T *); //Constructor
    NodeQueue(T); //Constructor
    ~NodeQueue(); //Destructor
    T *getData(); //Devuelve el dato del objeto
    NodeQueue<T> *getNextNode();//Siguiente nodo
};


template<class T>
void Queue<T>::push(T *dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeQueue<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
template<class T>
void Queue<T>::push(T dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeQueue<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
/**
 * Metodo para insertar en cola de prioridad
 */
template<class T>
void Queue<T>::pushNode(NodeQueue<T>* node) {
    if (lenght==0) _head = node;
    node->next = _head;
    _head = node;
    lenght++;
}

template<class T>
T Queue<T>::top() {
    pthread_mutex_lock( &mutexData );
    T returnVal = *(_head->getData());
    pthread_mutex_unlock( &mutexData );
    return returnVal;

}

template<class T>
void Queue<T>::pop() {
    pthread_mutex_lock( &mutexData );
    NodeQueue<T> * headTemp = _head;//Nodo para liberarlo
    _head = _head->getNextNode();
    lenght--;//Actualiza largo
    free(headTemp);//GarbageCollection
    pthread_mutex_unlock( &mutexData );
}

template<class T>
bool Queue<T>::empty() {
    return lenght == 0;
}
template<class T>
int Queue<T>::size() {
    return lenght;
}


//Nodes Methods
template<class T>
NodeQueue<T>::NodeQueue(T * t) {
    data = t;
    next = 0;
}
template<class T>
NodeQueue<T>::NodeQueue(T t) {
    data = static_cast<T*>(malloc(sizeof(T)));
    *data = t;
    next = 0;
}
template<class T>
NodeQueue<T>::~NodeQueue() {
    next = 0;
}
template<class T>
T *NodeQueue<T>::getData() {
    return data;
}
template<class T>
NodeQueue<T> *NodeQueue<T>::getNextNode() {
    return next;
}

#endif //PROJECTMIDGARDLOGIC_QUEUE_H
