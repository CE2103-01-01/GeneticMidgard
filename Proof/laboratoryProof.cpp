//
// Created by roberto on 02/05/15.
//

#include "laboratoryProof.h"

void laboratoryProof(){
    //Crea pthread, mutex y parametro
    pthread_t reproducer;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    void* parameter = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(parameter)) PThreadParam(0,&mutex);
    pthread_create(&reproducer,0,reproduction,parameter);
    pthread_join(reproducer,0);
}

void* reproduction(void* parameter){
    //Se obtiene el mutex
    pthread_mutex_t* mutex = static_cast<PThreadParam*>(parameter)->getMutex();
    //Instancia e inicializa el laboratorio
    LifeLaboratory* laboratory = static_cast<LifeLaboratory*>(malloc(sizeof(LifeLaboratory)));
    new(laboratory) LifeLaboratory(mutex);
    //Se crea controlador de tiempo
    struct timespec timeControler;
    timeControler.tv_nsec=0;
    timeControler.tv_sec=5;
    //Se crea el controlador de iteraciones
    int x = 0;
    //Crea cinco poblaciones de 100 habitantes
    DoubleList<Population> population = laboratory->createLife(NUMBER_OF_SUBJECTS,NUMBER_OF_POPULATIONS);
    pthread_mutex_lock(mutex);
    while(x<10){
        DoubleListIterator<Population>* iter = population.getIterator();
        while(iter){
            //Se crea una generacion de cada poblacion
            laboratory->createGeneration(iter->next(),NUMBER_OF_SUBJECTS/4);
        }
        std::cout<< "x: " << x << std::endl;
        x++;
        nanosleep(&timeControler, NULL);
    }
    pthread_mutex_unlock(mutex);
    return 0;
};