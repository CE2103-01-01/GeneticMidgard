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

    Subject* parrent1; //padre del individuo
    Subject* parrent2; //padre del individuo
    Genes genes;
    Weapon weapon;
    Armor armor;

public:
    Subject();
    uint8_t getAtack();// Se suma armor y la defensa de los genes
    uint8_t makeDamage();// Se suma ataque y weapon
    Genes getGenes(); // Retorna los genes del individuo
    Subject* getParrent1(); // Obtiene padre 1
    Subject* getParrent2(); // Obtiene padre 2
    void setParrent1(Subject* parrent1); //setea valor de padre 1
    void setParrent2(Subject* parrent2); //setea valor de padre 2
    void setGenes();
};


#endif //PROJECTMIDGARD_SUBJECT_H
