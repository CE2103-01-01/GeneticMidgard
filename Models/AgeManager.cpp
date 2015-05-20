//
// Created by roberto on 10/05/15.
//

#include "AgeManager.h"

/**Constructor
 */
AgeManager::AgeManager(){
    //Edda actual
    actualAge = static_cast<int*>(malloc(sizeof(int)));
    *actualAge = 0;
    //Sleep general
    generalSleep = static_cast<long*>(malloc(sizeof(long)));
    *generalSleep = 1000;
    //Thread de manejo de eddas
    managementThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    //Mutex
    generalMutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(generalMutex,NULL);
    //manejador de poblaciones
    populationManager = PopulationManager::getInstance(generalMutex);
    //Manejador de objetos moviles
    //objectManager = static_cast<movilObjectManager*>(malloc(sizeof(movilObjectManager)));
    //new(objectManager) movilObjectManager();
    pthread_create(managementThread,0,ageManagerThread, static_cast<void*>(this));
    pthread_join(*managementThread,NULL);
}

/**Destructor
 */
AgeManager::~AgeManager(){
    free(generalMutex);
    free(generalSleep);
    free(managementThread);
    free(populationManager);
 //   free(objectManager);
    free(actualAge);
}

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

void* ageManagerThread(void* parameter){
    AgeManager* excecutioner = static_cast<AgeManager*>(parameter);
    //Reserva espacio para parametro de pthread
    void* populationManagerThreadParameters = malloc(sizeof(PThreadParam));
    //Crea parametro de pthread
    new(static_cast<PThreadParam*>(populationManagerThreadParameters))
            PThreadParam(excecutioner->getPopulationManager(),excecutioner->getGeneralMutex());
    //Inicia el pthread del manejador de poblaciomnes
    pthread_create(excecutioner->getPopulationManager()->get_pthread(),0,populationManagerThread,populationManagerThreadParameters);
    pthread_join(*excecutioner->getPopulationManager()->get_pthread(),0);

    return NULL;
}