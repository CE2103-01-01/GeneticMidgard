//
// Created by roberto on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_LIFELABORATORY_H
#define PROJECTMIDGARDLOGIC_LIFELABORATORY_H

#include "../Data/Tree.h"
#include "ChromosomeMixer.h"
#include "../Models/Subject.h"
#include "../Models/Population.h"
#include "GeneralFitnessCalculator.h"
#include "../Constants.h"

class LifeLaboratory {
    Chromosome* selectChromosome(Chromosome*,Chromosome*);
    Subject* selectParents(Population*);
    Tree<Subject> *createPopulation(int,int);
public:
    void createGeneration(Population*,int,int);
    Population* createLife(int,int);
};


#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H