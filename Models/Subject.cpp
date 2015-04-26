//
// Created by pablo on 22/04/15.
//

#include "Subject.h"

/*Subject::Subject()
{
    father = NULL;
    mother = NULL;
}*/


void Subject::setFather(Subject *pFather)
{
    this->father = pFather;
}

Subject* Subject::getFather()
{
    return this->father;
}

void Subject::setMother(Subject *pMother)
{
    this->mother = pMother;
}

Subject* Subject::getMother()
{
    return this->mother;
}

Genes Subject::getGenes()
{
    return this->genes;
}



