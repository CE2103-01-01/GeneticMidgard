//
// Created by pablo on 22/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_QUEUE_H
#define PROJECTMIDGARDLOGIC_QUEUE_H

#include <malloc.h>
#include <pthread.h>

template<class T>class NodeStack;
template<class T>
class Stack {
private:
    pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
    NodeStack<T>* _head;
    unsigned int lenght;
    void pushNode(NodeStack<T>*);
public:
    void push(T*);
    void push(T);
    void pop();
    bool empty();
    int size();

    T top();
};
template<class T>
class Queue {
private:
    pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
    NodeStack<T>* _head;
    unsigned int lenght;
    void pushNode(NodeStack<T>*);
public:
    void push(T*);
    void push(T);
    void pop();
    bool empty();
    int size();

    T top();
};
template<class T>
class NodeStack
{
    friend class Stack<T>;

private:
    T* data;
    NodeStack<T> *next;
public:
    NodeStack(T *); //Constructor
    NodeStack(T); //Constructor
    ~NodeStack(); //Destructor
    T *getData(); //Devuelve el dato del objeto
    NodeStack<T> *getNextNode();//Siguiente nodo
};


template<class T>
void Stack<T>::push(T *dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeStack<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
template<class T>
void Stack<T>::push(T dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeStack<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
/**
 * Metodo para insertar en pila
 */
template<class T>
void Stack<T>::pushNode(NodeStack<T>* node) {
    if (lenght==0) _head = node;
    node->next = _head;
    _head = node;
    lenght++;
}

template<class T>
T Stack<T>::top() {
    pthread_mutex_lock( &mutexData );
    T returnVal = *(_head->getData());
    pthread_mutex_unlock( &mutexData );
    return returnVal;

}

template<class T>
void Stack<T>::pop() {
    pthread_mutex_lock( &mutexData );
    NodeStack<T> * headTemp = _head;//Nodo para liberarlo
    _head = _head->getNextNode();
    lenght--;//Actualiza largo
    free(headTemp);//GarbageCollection
    pthread_mutex_unlock( &mutexData );
}

template<class T>
bool Stack<T>::empty() {
    return lenght == 0;
}
template<class T>
int Stack<T>::size() {
    return lenght;
}


//Nodes Methods
template<class T>
NodeStack<T>::NodeStack(T * t) {
    data = t;
    next = 0;
}
template<class T>
NodeStack<T>::NodeStack(T t) {
    data = static_cast<T*>(malloc(sizeof(T)));
    *data = t;
    next = 0;
}
template<class T>
NodeStack<T>::~NodeStack() {
    next = 0;
}
template<class T>
T *NodeStack<T>::getData() {
    return data;
}
template<class T>
NodeStack<T> *NodeStack<T>::getNextNode() {
    return next;
}

template<class T>
void Stack<T>::push(T *dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeStack<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
template<class T>
void Stack<T>::push(T dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeStack<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
/**
 * Metodo para insertar en pila
 */
template<class T>
void Stack<T>::pushNode(NodeStack<T>* node) {
    if (lenght==0) _head = node;
    node->next = _head;
    _head = node;
    lenght++;
}

template<class T>
T Stack<T>::top() {
    pthread_mutex_lock( &mutexData );
    T returnVal = *(_head->getData());
    pthread_mutex_unlock( &mutexData );
    return returnVal;

}

template<class T>
void Stack<T>::pop() {
    pthread_mutex_lock( &mutexData );
    NodeStack<T> * headTemp = _head;//Nodo para liberarlo
    _head = _head->getNextNode();
    lenght--;//Actualiza largo
    free(headTemp);//GarbageCollection
    pthread_mutex_unlock( &mutexData );
}

template<class T>
bool Stack<T>::empty() {
    return lenght == 0;
}
template<class T>
int Stack<T>::size() {
    return lenght;
}

#endif //PROJECTMIDGARDLOGIC_QUEUE_H
