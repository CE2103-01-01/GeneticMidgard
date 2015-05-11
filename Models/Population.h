//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "../Data/Tree.h"
#include "../Algorithms/GeneralFitnessCalculator.h"
#include "Subject.h"

#ifndef PROJECTMIDGARD_POPULATION_H
#define PROJECTMIDGARD_POPULATION_H

class Population {
    pthread_mutex_t* mutex;
    pthread_t* reproduction_pthread;
    int* actualGeneration;
    int* populationSize;
    float* populationFitness;
    char* populationType;// tipo de la poblacion
    Tree<Subject>* populationTree; //lista de los individuos de la poblacion
    bool* defunct;
    void calculateFitness();
    void killEmAll();
public:
    Population(char); //constructor de la poblacion
    ~Population();// destructor por defecto
    void insertNewMember(Subject*, Subject*, Chromosome*);
    Tree<Subject>* getPopulationTree();
    Subject* getIndividual(int);// obtiene un individuo por medio de indice
    int getPopulationSize();// obtiene la cantidad de personas en la poblacion
    float getPopulationFitness();
    char getPopulationType();
    void updateGeneration();
    void createNewRandomMember();
    bool isDefunct();
    void exterminate();
    void init_pthread();
    pthread_t* get_pthread();
};

void* reproductionThread(void*);

#endif //PROJECTMIDGARD_POPULATION_H
