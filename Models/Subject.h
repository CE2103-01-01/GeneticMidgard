//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H

#include "Chromosome.h"
#include "Weapon.h"
#include "Armor.h"
#include "../Data/DoubleList.h"
#include "../libs/pugixml/pugixml.hpp"
#include <cstdlib>
#include <stdio.h>
#include "../Constants.h"


class Subject {

    int* generation;
    int* fitness;
    std::string profession;
    DoubleList<int> caracteristics;//lista de caracteristicas
    // TODO: el orden va edad-experiencia-vida-ataque-velocidad-defensa-inteligencia-magia-runes-energia-blot-supersticion
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
    void calculateFitness();//funcion de calcular fitness y set fitness
    int getGeneration();
    int getAge();
    int getExperience();
    Weapon* getWeapon();
    Armor* getArmor();
};


#endif //PROJECTMIDGARD_SUBJECT_H
