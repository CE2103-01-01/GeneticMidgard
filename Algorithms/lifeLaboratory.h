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
    void fillGeneration();
public:
    LifeLaboratory(Population*);
    LifeLaboratory(const LifeLaboratory& other);
    ~LifeLaboratory();
    void createGeneration();
    void createPopulation();
};

#endif //PROJECTMIDGARDLOGIC_LIFELABORATORY_H