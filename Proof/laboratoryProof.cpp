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
    ChromosomeMixer::getInstance();
    //Se obtiene el mutex
    pthread_mutex_t* mutex = static_cast<PThreadParam*>(parameter)->getMutex();
    //Instancia e inicializa el laboratorio
    LifeLaboratory* laboratory = static_cast<LifeLaboratory*>(malloc(sizeof(LifeLaboratory)));
    new(laboratory) LifeLaboratory(mutex);
    //Se crea controlador de tiempo
    struct timespec timeControler;
    timeControler.tv_nsec=500;
    timeControler.tv_sec=1;
    //Se crea el controlador de iteraciones
    int x = 0;
    pthread_mutex_lock(mutex);
    //Crea cinco poblaciones de 100 habitantes
    Population* population = static_cast<Population*>(malloc(sizeof(Population) * NUMBER_OF_POPULATIONS));
    laboratory->createLife(NUMBER_OF_SUBJECTS,NUMBER_OF_POPULATIONS, population);
    std::cout << "PEOPLE CREATED" <<std::endl;
    while(x<150){
        std::cout << "REPRODUCING..." <<std::endl;
        for(int i = 0; i<NUMBER_OF_POPULATIONS; i++){
            //Se crea una generacion de cada poblacion
            laboratory->createGeneration(population+i,NUMBER_OF_SUBJECTS/2);
            std::cout<< "SIZE OF: " << i << " = " << (population+i)->getPopulationSize() <<std::endl;
        }
        nanosleep(&timeControler, NULL);
        x++;
    }
    pthread_mutex_unlock(mutex);
    free(laboratory);
    return 0;
};