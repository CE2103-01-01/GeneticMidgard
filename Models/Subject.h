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

/** Clase Subject
 * @brief clase a la cual pertenecen todos los individuos vivos
 * @caracteristicas: edad, experiencia, salud, ataque, velocidad, defensa,
 *                   inteligencia, magia, runes-energia, blot, supersticion
*/
class Subject {
    int* generation;
    int* fitness;
    char* profession; //TODO: mejor usar un char que gasta menos espacio
    unsigned char* characteristics;//lista de caracteristicas
    Subject* father; //padre del individuo
    Subject* mother; //padre del individuo
    Chromosome* geneticInformation;
    Weapon* weapon;
    Armor* armor;
public:
    Subject();
    Subject(Subject*,Subject*,Chromosome*,int);
    int calculateDamage();  // TODO: implementar
    int calculateDefense(); // TODO: implementar
    void calculateFitness();//funcion de calcular fitness y set fitness
    Chromosome* getGeneticInformation();
    Subject* getFather(); // Obtiene padre 1
    Subject* getMother(); // Obtiene padre 2
    Weapon* getWeapon();
    Armor* getArmor();
    int getFitness();
    int getGeneration();
    unsigned char getHealth();
    unsigned char getAge();
    unsigned char getExperience();
};


#endif //PROJECTMIDGARD_SUBJECT_H
