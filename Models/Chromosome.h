//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_GENES_H
#define PROJECTMIDGARD_GENES_H

#include "../Constants.h"
#include "../Interface/Random.h"
#include "../libs/pugixml/pugixml.hpp"

class Chromosome {
    void* geneticData;
    int* numberOfGenes;
    int readLenghtFromXML();
public:
    Chromosome();
    Chromosome(void*);
    void* getGene(int);
    int getNumberOfGenes();
};


#endif //PROJECTMIDGARD_GENES_H
