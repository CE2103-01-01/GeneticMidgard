//
// Created by roberto on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H
#define PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H

#include "Population.h"

class PopulationManager {
    static pthread_t* managementThread;
    static pthread_mutex_t* mutex;
    static PopulationManager* singleton;
    int* actualID;
    int* activePopulations;
    Population* population;
    void init_war();
    void reproduce();
    public:
        PopulationManager(int);
        ~PopulationManager();
        void thread();
        void killEmAll();
        bool isSomeoneAlive();
        Population* getPopulation();
        static PopulationManager* getInstance();
        static pthread_t* get_pthread();
        void delete_pthread();
        void createLife();
        void mergePopulations();
        int getActivePopulations();
        int getActualID();
};

void* populationManagerThread(void*);

#endif //PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H
