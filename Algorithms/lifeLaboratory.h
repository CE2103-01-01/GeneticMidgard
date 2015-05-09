//
// Created by roberto on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_LIFELABORATORY_H
#define PROJECTMIDGARDLOGIC_LIFELABORATORY_H

#include "ChromosomeMixer.h"
#include "../Models/Population.h"
#include "../Data/DoubleList.h"

class LifeLaboratory {
    Population* labRats;
    void fillGeneration(int, int*);
    void selectParents(int, int*);
    bool checkSeleccions(Subject*, int*, int);
public:
    LifeLaboratory(Population*);
    LifeLaboratory(const LifeLaboratory& other);
    ~LifeLaboratory();
    void createGeneration(int);
    void createPopulation(int);
};

#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H