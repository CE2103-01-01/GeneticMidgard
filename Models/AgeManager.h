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
    bool evaluateSubject(Subject*);

    public:
        AgeManager();
        ~AgeManager();
        PopulationManager* getPopulationManager();
        movilObjectManager* getMovilObjectManager();
        pthread_mutex_t* getGeneralMutex();
        pthread_t* getManagementThread();
        long getGeneralSleep();
        int getActualAge();
        void thread();
};

void* ageManagerThread(void*);

#endif //PROJECTMIDGARDLOGIC_AGEMANAGER_H
