//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "../Data/Tree.h"
#include "../Algorithms/GeneralFitnessCalculator.h"
#include "Subject.h"

#ifndef PROJECTMIDGARD_POPULATION_H
#define PROJECTMIDGARD_POPULATION_H

class Population {
private:
    int* populationSize;
    float* populationFitness;
    char* populationType;// tipo de la poblacion
    Tree<Subject>* peopleTree; //lista de los individuos de la poblacion
    void calculateFitness();
public:
    Population(Tree<Subject>*,char,int); //constructor de la poblacion
    ~Population();// destructor por defecto
    void insertNewMember(Subject*, Chromosome*);
    Tree<Subject>* getPopulationTree();
    Subject* getIndividual(int);// obtiene un individuo por medio de indice
    int getPopulationSize();// obtiene la cantidad de personas en la poblacion
    float getPopulationFitness();
    char getPopulationType();
};

#endif //PROJECTMIDGARD_POPULATION_H
