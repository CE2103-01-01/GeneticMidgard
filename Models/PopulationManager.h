//
// Created by roberto on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H
#define PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H

#include "Population.h"

class PopulationManager {
    static pthread_t* managementThread;
    static pthread_t* warThread;
    static pthread_mutex_t* mutex;
    static PopulationManager* singleton;
    int* actualID;
    int* activePopulations;
    Population* population;
    void init_war();
    public:
        PopulationManager(int);
        ~PopulationManager();
        void thread();
        void killEmAll();
        bool isSomeoneAlive();
        Population* getPopulation();
        static PopulationManager* getInstance();
        static pthread_t* get_pthread();
        static pthread_t* get_war_pthread();
        void delete_pthread();
        void delete_war_pthread();
        void createLife();
        void reproduce();
        void mergePopulations();
        int getActivePopulations();
        int getActualID();
        void initFinalWar();
};

void* populationManagerThread(void*);
void* populationManagerWarThread(void*);

#endif //PROJECTMIDGARDLOGIC_POPULATIONMANAGER_H
