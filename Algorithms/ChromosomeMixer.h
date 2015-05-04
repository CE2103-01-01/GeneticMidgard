//
// Created by roberto on 27/04/15.
//

#ifndef PROJECTMIDGARD_CHROMOSOMEMIXER_H
#define PROJECTMIDGARD_CHROMOSOMEMIXER_H

#include "../Models/Chromosome.h"
#include "GeneralFitnessCalculator.h"

class ChromosomeMixer {
    static GeneralFitnessCalculator* calculator;
    static ChromosomeMixer* instance;
    public:
        ChromosomeMixer();
        static ChromosomeMixer* getInstance();
        Chromosome mix(Chromosome,Chromosome);

    GeneralFitnessCalculator *getCalculator();
};


#endif //PROJECTMIDGARD_CHROMOSOMEMIXER_H
