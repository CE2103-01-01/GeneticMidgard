//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H

#include "Chromosome.h"
#include "Weapon.h"
#include "Armor.h"

class Subject {
    int* health;
    int* generation;
    int* age;
    int* experience;//Experiencia
    int* fitness;
    Subject* father; //padre del individuo
    Subject* mother; //padre del individuo
    Chromosome* geneticInformation;
    Weapon* weapon;
    Armor* armor;

public:
    Subject();
    Subject(Subject*,Subject*);
    int makeDamage();// Se suma ataque y weapon
    void setFitness(int);
    int getAtack();// Se suma armor y la defensa de los genes
    Subject* getFather(); // Obtiene padre 1
    Subject* getMother(); // Obtiene padre 2
    Chromosome* getGeneticInformation();
    int getFitness();
    int getHealth();
    int getGeneration();
    int getAge();
    int getExperience();
    Weapon* getWeapon();
    Armor* getArmor();
};


#endif //PROJECTMIDGARD_SUBJECT_H
