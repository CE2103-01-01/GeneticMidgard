//
// Created by roberto on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_LIFELABORATORY_H
#define PROJECTMIDGARDLOGIC_LIFELABORATORY_H

#include "ChromosomeMixer.h"
#include "../Models/Population.h"
#include "../Data/DoubleList.h"

class LifeLaboratory {
    Chromosome* selectChromosome(Chromosome*,Chromosome*);
    void selectParents(Population*, DoubleList<Subject*>);
    Tree<Subject> *createPopulation(int,int);
    bool checkSeleccions(Subject*, DoubleList<Subject*>);
public:
    void createGeneration(Population*,int,int);
    Population* createLife(int,int);
};


#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H