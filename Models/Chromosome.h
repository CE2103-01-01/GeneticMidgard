//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_GENES_H
#define PROJECTMIDGARD_GENES_H

#include "../Constants.h"
#include "../Interface/Random.h"
#include "../libs/pugixml/pugixml.hpp"

class Chromosome {
    unsigned char* geneticData;
    int* numberOfGenes;
public:
    Chromosome();
    Chromosome(unsigned char*);
    unsigned char* getGene(int);
    int getNumberOfGenes();
    static int readLenghtFromXML();
};


#endif //PROJECTMIDGARD_GENES_H
