//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H

#include "Chromosome.h"
#include "../Algorithms/GeneralFitnessCalculator.h"
#include "../Data/PThreadParam.h"

/** Clase Subject
 * @brief clase a la cual pertenecen todos los individuos vivos
 * @caracteristicas: edad, experiencia, salud, ataque, velocidad, defensa,
 *                   inteligencia, magia, runes-energia, blot, supersticion,
 *                   arma, armadura
*/
class Subject {
    pthread_t lifeThread;
    int id;
    int* generation;
    float* fitness;
    const char* profession; //TODO: mejor usar un char que gasta menos espacio
    unsigned char* characteristics;//lista de caracteristicas
    const char* race;
    bool* alive;
    Subject* father; //padre del individuo
    Subject* mother; //padre del individuo
    Chromosome* geneticInformation;
    void calculateFitness();//funcion de calcular fitness y set fitness
public:
    Subject(int);
    Subject(Subject*,Subject*,Chromosome,int,int);
    ~Subject();
    int calculateDamage();  // TODO: implementar
    int calculateDefense(); // TODO: implementar
    Chromosome* getGeneticInformation();
    Subject* getFather(); // Obtiene padre 1
    Subject* getMother(); // Obtiene padre 2
    float getFitness();
    int getGeneration();
    unsigned char getWeapon();
    unsigned char  getArmor();
    unsigned char getHealth();
    unsigned char getAge();
    unsigned char getExperience();
    void setCharacteristic(int,char);
    bool isAlive();
    void kill();
    void life(void);
    int getID();
    pthread_t *get_p_thread();
    void start_p_thread();
};

void* subjectLife(void*);

#endif //PROJECTMIDGARD_SUBJECT_H
