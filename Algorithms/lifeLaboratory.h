//
// Created by roberto on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_LIFELABORATORY_H
#define PROJECTMIDGARDLOGIC_LIFELABORATORY_H

#include "../Data/Tree.h"
#include "ChromosomeMixer.h"
#include "../Models/Subject.h"
#include "../Algorithms/GeneralFitnessCalculator.h"

class LifeLaboratory {
    int* counterOfPeople;
    int* totalFitness;
    Chromosome* selectChromosome(Chromosome*,Chromosome*);
    Subject* selectParents(Tree<Subject>*);
public:
        Subject* createGeneration(Tree<Subject>*,int,int);
        Subject* createLife(int);
};


#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H