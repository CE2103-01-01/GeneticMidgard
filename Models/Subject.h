//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H

#include "Chromosome.h"
#include "../Algorithms/GeneralFitnessCalculator.h"
#include "../Data/PThreadParam.h"
#include "Terrain.h"

/** Clase Subject
 * @brief clase a la cual pertenecen todos los individuos vivos
 * @caracteristicas: edad, experiencia, salud, ataque, velocidad, defensa,
 *                   inteligencia, magia, runes-energia, blot, supersticion,
 *                   arma, armadura
*/
class Subject {
    Subject* father; //padre del individuo
    Subject* mother; //padre del individuo
    Subject* opponent;
    Chromosome* geneticInformation;
    Vector2D* position;
    pthread_t* lifeThread;
    pthread_cond_t* condition;
    pthread_mutex_t* mutex;
    int* actualYear;
    int* generation;
    long* id;
    float* fitness;
    bool* selected;
    unsigned char* characteristics;//vida-experiencia-arma-armadura-profesion
    void calculateFitness();//funcion de calcular fitness y set fitness
public:
    Subject(long,int*,unsigned char*,Vector2D);
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
    void attack();
    void life(void);
    bool isAlive();
    bool isSelected();
    void changeSelection(bool);
    void kill();
    pthread_t* get_p_thread();
    void start_p_thread();
    void setOppenent(Subject*);
    void delete_p_thread();
};

void* subjectLife(void*);

#endif //PROJECTMIDGARD_SUBJECT_H
