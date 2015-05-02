//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"

/** Construye una poblacion
 * @param Tree<Subject>* peopleTreeParam: primera generacion
 * @param char populationTypeParam: tipo de poblacion
 */
Population::Population(Tree<Subject>* peopleTreeParam, char populationTypeParam,
                       int populationSizeParam){
    //Reserva espacios
    populationType = static_cast<char*>(malloc(sizeof(char)));
    populationFitness = static_cast<float*>(malloc(sizeof(float)));
    populationSize = static_cast<int*>(malloc(sizeof(int)));
    //Llena espacios
    *populationType = populationTypeParam;
    *populationSize = populationSizeParam;
    peopleTree = peopleTreeParam;
    calculateFitness();
}

/**@brief: libera el espacio utilizado
 */
Population::~Population() {
    free(populationType);
    free(peopleTree);
}

/**@brief: calcula el fitness
 */
void Population::calculateFitness(){
    //TODO: implementar
}

/**@brief: inserta un nuevo miembro
 * @param Subject* parents: padres del individuo
 * @param Chromosome* chromosome: cromosoma del individuo
 */
void Population::insertNewMember(Subject* parents, Chromosome* chromosome) {
    //TODO: implementar
}

/**@brief: permite acceder a un individuo mediante su id
 * @param int id: identificacion del personaje, formato NumeroNacimiento-NumeroPoblacion
 * @return Subject*
 */
Subject* Population::getIndividual(int id) {
    return peopleTree->searchElement(id/10);
}

/**@brief devuelve el arbol de poblacion
 * @return Tree<Subject>*
 */
Tree<Subject>* Population::getPopulationTree(){
    return peopleTree;
};

/**@brief devuelve el fitness de poblacion
 * @return int
 */
float Population::getPopulationFitness(){
    return *populationFitness;
}

/**@brief devuelve el tamano de poblacion
 * @return int
 */
int Population::getPopulationSize(){
    return *populationSize;
}

/**@brief devuelve el tipo de poblacion
 * @return char
 */
char Population::getPopulationType() {
    return *populationType;
}