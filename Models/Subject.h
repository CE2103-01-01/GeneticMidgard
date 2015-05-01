//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H

#include "Chromosome.h"

/** Clase Subject
 * @brief clase a la cual pertenecen todos los individuos vivos
 * @caracteristicas: edad, experiencia, salud, ataque, velocidad, defensa,
 *                   inteligencia, magia, runes-energia, blot, supersticion,
 *                   arma, armadura
*/
class Subject {
    int* generation;
    int* fitness;
    const char* profession; //TODO: mejor usar un char que gasta menos espacio
    unsigned char* characteristics;//lista de caracteristicas
    const char* race;
    Subject* father; //padre del individuo
    Subject* mother; //padre del individuo
    Chromosome* geneticInformation;
public:
    Subject();
    Subject(Subject*,Subject*,Chromosome*,int);
    int calculateDamage();  // TODO: implementar
    int calculateDefense(); // TODO: implementar
    void calculateFitness();//funcion de calcular fitness y set fitness
    Chromosome* getGeneticInformation();
    Subject* getFather(); // Obtiene padre 1
    Subject* getMother(); // Obtiene padre 2
    int getFitness();
    int getGeneration();
    unsigned char getWeapon();
    unsigned char  getArmor();
    unsigned char getHealth();
    unsigned char getAge();
    unsigned char getExperience();
    void setHealth(int);
    void setAttack(int);
    void setSpeed(int);
    void setDefense(int);
    void setIntelligent(int);
    void setMagic(int);
    void setRunes(int);
    void setEnergy(int);
    void setBlot(int);
    void setSuperstition(int);
};


#endif //PROJECTMIDGARD_SUBJECT_H
