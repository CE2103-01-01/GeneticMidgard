//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_GENES_H
#define PROJECTMIDGARD_GENES_H

#include "../Constants.h"
#include "../Interface/Random.h"

class Chromosome {
    unsigned char* geneticData;
    int* numberOfGenes;
public:
    Chromosome();
    Chromosome(unsigned char*);
    unsigned char* getGene(int);
    int getNumberOfGenes();
};


#endif //PROJECTMIDGARD_GENES_H
