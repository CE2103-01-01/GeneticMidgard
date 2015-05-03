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
    void fillGeneration(Population*, int, DoubleList<Subject>*);
    DoubleList<Subject>* selectParents(Population*, int);
    bool checkSeleccions(Subject*, DoubleList<Subject>*);
    Chromosome* selectChromosome(Chromosome*,Chromosome*);
    Tree<Subject> createPopulation(int,int);
public:
    LifeLaboratory(pthread_mutex_t*);
    void createGeneration(Population*,int);
    DoubleList<Population> createLife(int,int);
};


#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H