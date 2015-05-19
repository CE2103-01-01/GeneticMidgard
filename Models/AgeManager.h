//
// Created by roberto on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_AGEMANAGER_H
#define PROJECTMIDGARDLOGIC_AGEMANAGER_H

#include <pthread.h>
#include "PopulationManager.h"
#include "movilObjectManager.h"

class AgeManager {
    pthread_mutex_t* generalMutex;
    pthread_t* managementThread;
    long* generalSleep;
    int* actualAge;
    PopulationManager* populationManager;
    movilObjectManager* objectManager;
    void changeAge();
    void evaluateEvolution();
    public:
        AgeManager();
        ~AgeManager();
        PopulationManager* getPopulationManager();
        pthread_mutex_t* getGeneralMutex();
        void thread();
};

void* ageManagerThread(void*);

#endif //PROJECTMIDGARDLOGIC_AGEMANAGER_H
