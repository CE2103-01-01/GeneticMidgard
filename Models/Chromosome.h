//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_GENES_H
#define PROJECTMIDGARD_GENES_H

#include "../Constants.h"
#include "../Interface/Random.h"

class Chromosome {
    unsigned char* geneticData;
public:
    Chromosome(unsigned char*,unsigned char*,unsigned char*);
    Chromosome(unsigned char*);
    Chromosome(const Chromosome&);
    ~Chromosome();
    unsigned char getGene(int);
};

#endif //PROJECTMIDGARD_GENES_H
