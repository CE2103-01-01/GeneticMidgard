//
// Created by pablo on 22/04/15.
//

#include "Subject.h"

/*Subject::Subject()
{
    father = NULL;
    mother = NULL;
}*/


void Subject::setParrent1(Subject *parrent1)
{
    this->father = parrent1;
}

Subject* Subject::getParrent1()
{
    return this->father;
}

void Subject::setParrent2(Subject *parrent2)
{
    this->mother = parrent2;
}

Subject* Subject::getParrent2()
{
    return this->mother;
}

Genes Subject::getGenes()
{
    return this->genes;
}



