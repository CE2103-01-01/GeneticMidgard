//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"

/** Construye una poblacion
 * @param Tree<Subject>* peopleParam: primera generacion
 * @param char populationTypeParam: tipo de poblacion
 */
Population::Population(Tree<Subject>* peopleParam, char populationTypeParam,
                       int populationSizeParam){
    //Reserva espacios
    populationType = static_cast<char*>(malloc(sizeof(char)));
    populationFitness = static_cast<int*>(malloc(sizeof(int)));
    populationSize = static_cast<int*>(malloc(sizeof(int)));
    //Llena espacios
    *populationType = populationTypeParam;
    *populationFitness = 0;
    *populationSize = populationSizeParam;
    people = peopleParam;
}

/**@brief: libera el espacio utilizado
 */
Population::~Population() {
    free(populationType);
    free(people);
}

/**@brief: calcula el fitness
 */
void Population::calculateFitness(){
    //TODO: implementar
};

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
    return people->searchElement(id/10);
}

/**@brief devuelve el arbol de poblacion
 * @return Tree<Subject>*
 */
Tree<Subject>* getPopulationTree(){
    return people;
};

/**@brief devuelve el fitness de poblacion
 * @return int
 */
int getPopulationFitness(){
    return *populationFitness;
}

/**@brief devuelve el tamano de poblacion
 * @return int
 */
int getPopulationSize(){
    return *populationSize;
}

/**@brief devuelve el tipo de poblacion
 * @return char
 */
char Population::getPopulationType() {
    return *populationType;
}