//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H


#include "Genes.h"
#include "Weapon.h"
#include "Armor.h"

class Subject {
private:
    unsigned int health;
    unsigned int generation;
    unsigned int age;
    unsigned int exp;//Experiencia
    Genes genes;
    Weapon weapon;
    Armor armor;

public:
    unsigned int getAtack();// Se suma armor y la defensa de los genes
    unsigned int makeDamage();// Se suma ataque y weapon
};


#endif //PROJECTMIDGARD_SUBJECT_H
