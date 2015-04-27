//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//
#include "../Data/Tree.h"
#include "Subject.h"
#include <iostream>
#include "../Constants.h"

#ifndef PROJECTMIDGARD_POPULATION_H
#define PROJECTMIDGARD_POPULATION_H

class Population {
private:
    Tree<Subject>* people; //lista de los individuos de la poblacion
    char* populationType;// tipo de la poblacion


public:
    Population(int,char); //constructor de la poblacion
    ~Population();// destructor por defecto
    Subject getIndividual(int);// obtiene un individuo por medio de indice
    Subject getFittest();// obtiene el mejor individuo de la poblacion
    int getPopulationSize();// obtiene la cantidad de personas en la poblacion
    std::string getPopulationType();// obtiene el tipo de la poblacion;
};

#endif //PROJECTMIDGARD_POPULATION_H
