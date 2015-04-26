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
    uint16_t id;
    uint8_t health;
    uint8_t generation;
    uint8_t age;
    uint8_t exp;//Experiencia
    int fitness;

    Subject*father; //padre del individuo
    Subject*mother; //madre del individuo
    Genes genes;
    Weapon weapon;
    Armor armor;

public:
    Subject();
    uint8_t getAtack();// Se suma armor y la defensa de los genes
    uint8_t makeDamage();// Se suma ataque y weapon
    Genes getGenes(); // Retorna los genes del individuo
    Subject*getFather(); // Obtiene padre 1
    Subject*getMother(); // Obtiene padre 2
    void setFather(Subject *pFather); //setea valor de padre 1
    void setMother(Subject *pMother); //setea valor de padre 2
    void setGenes();
    void setFitness(int);
    int getFitness();
};


#endif //PROJECTMIDGARD_SUBJECT_H
