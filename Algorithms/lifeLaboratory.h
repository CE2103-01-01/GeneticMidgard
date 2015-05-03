//
// Created by roberto on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_LIFELABORATORY_H
#define PROJECTMIDGARDLOGIC_LIFELABORATORY_H

#include "ChromosomeMixer.h"
#include "../Models/Population.h"
#include "../Data/DoubleList.h"

class LifeLaboratory {
    pthread_mutex_t* mutex;
    void fillGeneration(Population*, int, int*);
    void selectParents(Population*, int, int*);
    bool checkSeleccions(Subject*, int*, int);
    void createPopulation(int,Population*);
public:
    LifeLaboratory(pthread_mutex_t*);
    void createGeneration(Population*,int);
    void createLife(int,int, Population*);
};


#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H