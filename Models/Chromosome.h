//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_GENES_H
#define PROJECTMIDGARD_GENES_H

#include "../Constants.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include "../libs/pugixml/pugixml.hpp"

class Chromosome {
private:
    void* geneticData;
    int* numberOfGenes;
public:
    Chromosome();
    Chromosome(void*);
    void* getGene(int);
    int getNumberOfGenes();
};


#endif //PROJECTMIDGARD_GENES_H
