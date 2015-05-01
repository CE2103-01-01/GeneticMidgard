//
// Created by roberto on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_LIFELABORATORY_H
#define PROJECTMIDGARDLOGIC_LIFELABORATORY_H

#include "../Data/Tree.h"
#include "ChromosomeMixer.h"
#include "../Models/Subject.h"

class lifeLaboratory {
    Chromosome* selectChromosome(Chromosome*,Chromosome*);
    Subject* selectParents(Tree*);
    public:
        Subject* createGeneration(Tree*,int);
};


#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H