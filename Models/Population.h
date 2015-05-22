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
    pthread_t* reproduction_pthread;
    int* smallerIndexOnTree;
    int* activePopulationsOnManager;
    int* actualGeneration;
    int* populationSize;
    char* populationType;// tipo de la poblacion
    Tree<Subject>* populationTree; //lista de los individuos de la poblacion
    Subject** fittest;
    bool* defunct;
    void killEmAll();
    Vector2D* position;
public:
    Population(char, int*); //constructor de la poblacion
    ~Population();// destructor por defecto
    void insertNewMember(Subject*, Subject*, Chromosome*);
    Tree<Subject>* getPopulationTree();
    Subject* getIndividual(int);// obtiene un individuo por medio de indice
    int getPopulationSize();// obtiene la cantidad de personas en la poblacion
    char getPopulationType();
    void updateGeneration();
    void createNewRandomMember();
    bool isDefunct();
    void exterminate();
    void init_pthread();
    pthread_t* get_pthread();
    void delete_pthread();
    void updateFittest(Subject*);
    void updateFittest();
    void fillFittest(int);
    Subject** getFittest();
};

void* reproductionThread(void*);

#endif //PROJECTMIDGARD_POPULATION_H
