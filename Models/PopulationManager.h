//
// Created by roberto on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H
#define PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H

#include "Population.h"

class PopulationManager {
    static pthread_t* managementThread;
    static PopulationManager* singleton;
    int* actualID;
    int* activePopulations;
    Population* population;
    Population* mergePopulations();
    public:
        PopulationManager(int,pthread_mutex_t*);
        ~PopulationManager();
        void thread();
        void killEmAll();
        bool isSomeoneAlive();
        int getActivePopulations();
        Population* getPopulation();
        static PopulationManager* getInstance(pthread_mutex_t*);
        static pthread_t* get_pthread();
        void delete_pthread();
};

void* populationManagerThread(void*);

#endif //PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H
