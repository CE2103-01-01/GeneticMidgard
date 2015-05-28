//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "../Data/Tree.h"
#include "../Algorithms/GeneralFitnessCalculator.h"
#include "Subject.h"
#include "Terrain.h"

#ifndef PROJECTMIDGARD_POPULATION_H
#define PROJECTMIDGARD_POPULATION_H

class Population {
    unsigned char* colors;
    int* activePopulationsOnManager;
    int* actualGeneration;
    int* populationSize;
    char* populationType;// tipo de la poblacion
    Tree<Subject>* populationTree; //lista de los individuos de la poblacion
    Subject** fittest;
    bool* defunct;
    Vector2D* position;
    void killEmAll();
public:
    Population(char, int*); //constructor de la poblacion
    ~Population();// destructor por defecto
    void createNewRandomMember();
    void insertNewMember(Subject*, Subject*, Chromosome*);
    void insertNewMember(Subject*);
    void updateGeneration();
    void updateFittest(Subject*);
    void updateFittest();
    void exterminate();
    bool isDefunct();
    void fillFittest();
    Subject** getFittest();
    int getActualID();
    Subject* getSubject(long);
    unsigned char getColors();
};

void* reproductionThread(void*);

#endif //PROJECTMIDGARD_POPULATION_H
