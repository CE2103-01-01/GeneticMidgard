//
// Created by roberto on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_AGEMANAGER_H
#define PROJECTMIDGARDLOGIC_AGEMANAGER_H

#include <pthread.h>
#include "PopulationManager.h"

class AgeManager {
    pthread_mutex_t* generalMutex;
    long* generalSleep;
    PopulationManager* manager;
    int* actualAge;
    void changeAge();
    void evaluateEvolution();
    void thread();
    public:
        AgeManager();
        ~AgeManager();
};

void* ageManagerThread(void*);

#endif //PROJECTMIDGARDLOGIC_AGEMANAGER_H
