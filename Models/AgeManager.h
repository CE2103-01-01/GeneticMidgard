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
    int* actualAge;
    void changeAge();
    void evaluateEvolution();
    bool evaluateSubject(Subject*);

    public:
        AgeManager();
        ~AgeManager();
        pthread_mutex_t* getGeneralMutex();
        void thread();
        void delete_p_thread();
        void initPopulationManager();
};

void* ageManagerThread(void*);

#endif //PROJECTMIDGARDLOGIC_AGEMANAGER_H
