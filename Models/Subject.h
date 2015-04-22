//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H


#include <stdint.h>
#include "Genes.h"
#include "Weapon.h"
#include "Armor.h"

class Subject {
private:
    uint8_t health;
    uint8_t generation;
    uint8_t age;
    uint8_t exp;//Experiencia
    Genes genes;
    Weapon weapon;
    Armor armor;

public:
    uint8_t getAtack();// Se suma armor y la defensa de los genes
    uint8_t makeDamage();// Se suma ataque y weapon
};


#endif //PROJECTMIDGARD_SUBJECT_H
