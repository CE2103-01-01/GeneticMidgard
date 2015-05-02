//
// Created by roberto on 01/05/15.
//

#include "lifeLaboratory.h"

Chromosome* LifeLaboratory::selectChromosome(Chromosome* firstSon,Chromosome* secondSon){
    //TODO: implementar
}

/**
 *
 */
Subject* LifeLaboratory::selectParents(Population* population){
    //TODO: implementar
}

/**@brief: genera un arbol de poblacion
 * @param int populationSize: cantidad de individuos
 * @param int populationNumber: numero de poblacion
 * @return Tree<Subject>*
 */
Tree<Subject>* LifeLaboratory::createPopulation(int populationSize, int populationNumber) {
    //Reserva espacio para el arbol
    Tree<Subject>* toReturn = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    //Crea el arbol
    new(toReturn) Tree<Subject>(TREE_SIZE);
    for (int i = 0; i < populationSize; i++) {
        //Crea un sujeto
        //Si es sujeto numero 3 de poblacion 5, su id sera 35 y estara en posicion 3
        Subject tmp = Subject(i*10 + populationNumber);
        //Introduce el sujeto
        toReturn->insertElement(tmp);
    }
    return toReturn;
}

/**@brief: genera cierta cantidad de poblaciones
 * @param int populationSize: numero de miembros
 * @param int populationNumber: numero de poblaciones
 * @return Population*
 */
Population* LifeLaboratory::createLife(int populationSize, int populationNumber){
    //Reserva el espacio de las poblaciones
    Population* toReturn = static_cast<Population*>(malloc(sizeof(Population)*populationNumber));
    for (int i = 0; i < populationNumber; i++) {
        //Crea un arbol de poblacion
        Tree<Subject>* people = createPopulation(populationSize,i);
        //Llena una poblacion
        new (toReturn + i*sizeof(Population)) Population(people, (char)populationNumber, populationSize);
    }
}

/** Metodo que genera una nueva generacion
 * @param Tree* population: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param int generationNumber: numero de la generacion a crear
 */
void LifeLaboratory::createGeneration(Population* population, int numberOfNewSubjects, int generationNumber){
    //Reserva espacio para N sujetos segun parametro
    Subject* newGeneration = static_cast<Subject*> (malloc(sizeof(Subject)*numberOfNewSubjects));
    //Llena la nueva generacion
    for (int i = 0; i < numberOfNewSubjects; ++i) {
        //Busca padres
        Subject* parents = selectParents(population);
        //Reserva espacio para los cromosomas resultantes
        Chromosome* optionsToReproduce = static_cast<Chromosome*>(malloc(2*sizeof(Chromosome)));
        //Mezcla cromosomas
        ChromosomeMixer::mix(parents->getGeneticInformation(),
                             (parents+sizeof(Subject))->getGeneticInformation(),
                             optionsToReproduce);
        //Evalua cromosomas
        Chromosome* luckyChromosome = selectChromosome(optionsToReproduce,optionsToReproduce+sizeof(Chromosome));
        //Crea el nuevo sujeto
        population->insertNewMember(parents,luckyChromosome);
    }
}