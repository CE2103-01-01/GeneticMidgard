//
// Created by roberto on 10/05/15.
//

#include "AgeManager.h"

AgeManager::AgeManager(){
    generalMutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(generalMutex,NULL);
    PopulationManager* populationManager = PopulationManager::getInstance(generalMutex);
}

AgeManager::~AgeManager(){}

void AgeManager::thread(){
}

void AgeManager::evaluateEvolution(){}

pthread_mutex_t* AgeManager::getGeneralMutex(){
    return generalMutex;
}

PopulationManager* AgeManager::getPopulationManager(){
    return populationManager;
}

void AgeManager::changeAge(){}

void* populationManagerThread(void* parameter){
    AgeManager* excecutioner = static_cast<AgeManager*>(parameter);
    //Reserva espacio para parametro de pthread
    void* populationManagerThreadParameters = malloc(sizeof(PThreadParam));
    //Crea parametro de pthread
    new(static_cast<PThreadParam*>(populationManagerThreadParameters))
            PThreadParam(excecutioner->getPopulationManager(),excecutioner->getGeneralMutex());
    //Inicia el pthread del manejador de poblaciomnes
    pthread_create(excecutioner->getPopulationManager()->get_pthread(),0,populationManagerThread,populationManagerThreadParameters);
    while(true){
        excecutioner->thread();
    }

    return 0;
}