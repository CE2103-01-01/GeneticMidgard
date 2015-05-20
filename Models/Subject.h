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
    Subject* father; //padre del individuo
    Subject* mother; //padre del individuo
    Chromosome* geneticInformation;
    pthread_t* lifeThread;
    int* position;
    int* actualYear;
    int* generation;
    long* id;
    float* fitness;
    unsigned char* characteristics;//vida-experiencia-arma-armadura-profesion
    void calculateFitness();//funcion de calcular fitness y set fitness
public:
    Subject(long,int*);
    Subject(Subject*,Subject*,Chromosome*,long,long,int*);
    Subject(const Subject&);
    ~Subject();;
    long getGeneration();
    long getID();
    Chromosome* getGeneticInformation();
    Subject* getFather(); // Obtiene padre 1
    Subject* getMother(); // Obtiene padre 2
    float getFitness();
    unsigned char getCharacteristic(int);
    void setCharacteristic(unsigned char, int);
    void attack(Subject*);
    void life(void);
    bool isAlive();
    void kill();
    pthread_t* get_p_thread();
    void start_p_thread();
};

void* subjectLife(void*);

#endif //PROJECTMIDGARD_SUBJECT_H
