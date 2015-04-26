//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_GENES_H
#define PROJECTMIDGARD_GENES_H

#include "../Constants.h"
#include <stdlib.h>

class Genes {
private:
    void* dna;

public:
    Genes(char pDna[Gene::lenght]);
    Genes(void* pDna);//largo: 8 bits * Gene::lenght;
    char getGene(Gene gen);
};


#endif //PROJECTMIDGARD_GENES_H
