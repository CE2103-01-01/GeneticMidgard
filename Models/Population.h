//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//
#include "../Data/DoubleList.h"
#include "Subject.h"
#include <iostream>
#ifndef PROJECTMIDGARD_POPULATION_H
#define PROJECTMIDGARD_POPULATION_H
class Population {
private:
    DoubleList<Subject> people; //lista de los individuos de la poblacion
    std::string populationType;// tipo de la poblacion


public:
    Population(int,std::string); //constructor de la poblacion
    ~Population();// destructor por defecto
    Subject getIndividual(int);// obtiene un individuo por medio de indice
    Subject getFittest();// obtiene el mejor individuo de la poblacion
    int getPopulationSize();// obtiene la cantidad de personas en la poblacion
    std::string getPopulationType();// obtiene el tipo de la poblacion;



};


#endif //PROJECTMIDGARD_POPULATION_H
