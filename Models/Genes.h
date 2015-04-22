//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_GENES_H
#define PROJECTMIDGARD_GENES_H


#include "../Data/BitVector.h"

class Genes {
private:
    BitVector dna;

public:
    unsigned int getInmuneSystem();
    unsigned int getInteligence();
    unsigned int getAttack();
    unsigned int getDefense();
    unsigned int getVitalEnergy();
    unsigned int getBlot();
    unsigned int getRunes();
    unsigned int getSuperstition();
    bool getGender();// T:Male F:Female
};


#endif //PROJECTMIDGARD_GENES_H
