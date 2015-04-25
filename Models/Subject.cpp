//
// Created by pablo on 22/04/15.
//

#include "Subject.h"

/*Subject::Subject()
{
    parrent1 = NULL;
    parrent2 = NULL;
}*/


void Subject::setParrent1(Subject *parrent1)
{
    this->parrent1 = parrent1;
}

Subject* Subject::getParrent1()
{
    return this->parrent1;
}

void Subject::setParrent2(Subject *parrent2)
{
    this->parrent2 = parrent2;
}

Subject* Subject::getParrent2()
{
    return this->parrent2;
}

Genes Subject::getGenes()
{
    return this->genes;
}



