//
// Created by pablo on 29/04/15.
//

#include <stdlib.h>
#include <iostream>

#ifndef PROJECTMIDGARD_PRIORITYQUEUE_H
#define PROJECTMIDGARD_PRIORITYQUEUE_H

template<class T>class NodeQ;
template<class T>
class PriorityQueue {
private:
    pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
    NodeQ<T>* _head;
    unsigned int lenght;
    void pushNode(NodeQ<T>*);
    PriorityQueue(const PriorityQueue<T> &other);
public:
    PriorityQueue();

    ~PriorityQueue();


    void push(T*);
    void push(T);
    void pop();
    bool empty();
    int size();

    T top();
};

template<class T>
class NodeQ
{
friend class PriorityQueue<T>;

private:
    T* data;
    NodeQ<T> *next;
    pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
public:
    NodeQ(T *); //Constructor
    NodeQ(T); //Constructor
    NodeQ(const NodeQ<T>&); //Constructor
    ~NodeQ(); //Destructor
    T getData(); //Devuelve el dato del objeto
    NodeQ<T> *getNextNode();//Siguiente nodo
};


#endif //PROJECTMIDGARD_PRIORITYQUEUE_H
template<class T>
void PriorityQueue<T>::push(T *dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeQ<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
template<class T>
void PriorityQueue<T>::push(T dato) {
    pthread_mutex_lock( &mutexData );
    pushNode(new NodeQ<T>(dato));
    pthread_mutex_unlock( &mutexData );
}
/**
 * Metodo para insertar en cola de prioridad
 */
template<class T>
void PriorityQueue<T>::pushNode(NodeQ<T>* node) {
    if (lenght==0) _head = node;
    else
    {
        NodeQ<T> *prevNodeToCompare = 0;
        NodeQ<T> *nodeToCompare = _head;
        for (int i = 0; i < lenght; ++i) {
            T dato = nodeToCompare->getData();
            if (dato<node->getData()){
                if (prevNodeToCompare == 0) {//insert in head
                    node->next = _head;
                    _head = node;
                }
                else{
                    prevNodeToCompare->next = node;
                    node->next = nodeToCompare;
                }
                lenght++;
                return;// exit after insert
            }
            prevNodeToCompare = nodeToCompare;
            nodeToCompare = nodeToCompare->getNextNode();
        }
        prevNodeToCompare->next=node;// insert al final
    }
    lenght++;
}

template<class T>
T PriorityQueue<T>::top() {
    pthread_mutex_lock( &mutexData );
    T returnVal = (_head->getData());
    pthread_mutex_unlock( &mutexData );
    return returnVal;
}

template<class T>
void PriorityQueue<T>::pop() {
    if (!_head) return;
    pthread_mutex_lock( &mutexData );
    NodeQ<T> * headTemp = _head;//Nodo para liberarlo
    _head = _head->getNextNode();
    lenght--;//Actualiza largo
    pthread_mutex_unlock( &mutexData );
}

template<class T>
bool PriorityQueue<T>::empty() {
    return lenght == 0;
}
template<class T>
int PriorityQueue<T>::size() {
    return lenght;
}


//Nodes Methods
template<class T>
NodeQ<T>::NodeQ(T * t) {
    data = t;
    next = 0;
}
template<class T>
NodeQ<T>::NodeQ(T t) {
    data = static_cast<T*>(malloc(sizeof(T)));
    *data = t;
    next = 0;
}
template<class T>
NodeQ<T>::~NodeQ() {
    next = 0;
    if(data)
    free(data);
}
template<class T>
T NodeQ<T>::getData() {
    if (!data)
        std::cerr<<"Null Pointer Exception"<<std::endl;
    return *data;
}
template<class T>
NodeQ<T> *NodeQ<T>::getNextNode() {
    return next;
}
template<class T>
NodeQ<T>::NodeQ(const NodeQ<T>& other) {
    data = static_cast<T*>(malloc(sizeof(T)));
    *data = *other.data;
    next = 0;
}
template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue &other) {
    std::cerr<<"WTF Copy Constructor"<<std::endl;
    NodeQ<T> * node = other._head;
    while(!node) {
        push(node->getData());
        node = node->getNextNode();
    }
}
template<class T>
PriorityQueue<T>::PriorityQueue() {
    _head = 0;
    lenght =0;
}
template<class T>
PriorityQueue<T>::~PriorityQueue() {
    std::cout << "Destruct PQ" << std::endl;
    NodeQ<T> * node = _head;
    while(!node) {
        NodeQ<T> * toFree = node;
        node = node->getNextNode();
        free(toFree);
    }
}
