//
// Created by roberto on 25/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_GOD_H
#define PROJECTMIDGARDLOGIC_GOD_H

#include <malloc.h>
#include "../Interface/Random.h"

#define NUMBER_OF_ATTRIBUTES  5
#define POSITION_OF_GOD_ATTRIBUTE_LIFE 0
#define POSITION_OF_GOD_ATTRIBUTE_ATTACK 1
#define POSITION_OF_GOD_ATTRIBUTE_DEFENSE 2
#define POSITION_OF_GOD_ATTRIBUTE_WEAPON 3
#define POSITION_OF_GOD_ATTRIBUTE_ARMOR 4

class God{
    unsigned char* attributes;
    public:
        God();
        God(const God&);
        ~God();
        bool isAlive();
        unsigned char getAttribute(int);
        void decreseLife(unsigned char);
};


#endif //PROJECTMIDGARDLOGIC_GOD_H
