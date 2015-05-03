//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"

/** Construye una poblacion
 * @param Tree<Subject>* peopleTreeParam: primera generacion
 * @param char populationTypeParam: tipo de poblacion
 */
Population::Population(char populationTypeParam){
    //Reserva espacios
    populationType = static_cast<char*>(malloc(sizeof(char)));
    populationFitness = static_cast<float*>(malloc(sizeof(float)));
    populationSize = static_cast<int*>(malloc(sizeof(int)));
    actualGeneration = static_cast<int*>(malloc(sizeof(int)));
    populationTree = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    //Llena espacios
    *populationType = populationTypeParam;
    *populationSize = 0;
    *actualGeneration = 1;
    *populationFitness = 0;
    new(populationTree) Tree<Subject>(TREE_SIZE);
}

/**@brief: libera el espacio utilizado
 */
Population::~Population() {
}

/**@brief: calcula el fitness
 */
void Population::calculateFitness(){
    (*populationFitness) = 0;
    for (int i = 1; i <= (*populationSize); i++) {
        (*populationFitness) += populationTree->searchElement(i-1)->getFitness();
    }
}

/**@brief: inserta un nuevo miembro
 * @param Subject* father: padre del individuo
 * @param Subject* mother: madre del individuo
 * @param Chromosome* chromosome: cromosoma del individuo
 */
void Population::insertNewMember(Subject* father, Subject* mother, Chromosome chromosome) {
    (*populationSize)++;
    populationTree->insertElement(
            Subject(father, mother, chromosome, (*actualGeneration), (*populationSize)*10 + (*populationType)),
            (*populationSize));
    Subject* newMember = populationTree->searchElement(*populationSize);
    (*populationFitness) += newMember->getFitness();
    newMember->start_p_thread();
}

/**@brief: inserta un nuevo miembro random
 */
void Population::createNewRandomMember() {
    (*populationSize)++;
    populationTree->insertElement(Subject((*populationSize)*10 + (*populationType)),(*populationSize));
    Subject* newMember = populationTree->searchElement(*populationSize);
    (*populationFitness) += newMember->getFitness();
    std::cout << "Se crea: " << newMember << " con ID: " << newMember->getID() <<std::endl;
    newMember->start_p_thread();
}

/**@brief: permite acceder a un individuo mediante su id
 * @param int id: identificacion del personaje, formato NumeroNacimiento-NumeroPoblacion
 * @return Subject*
 */
Subject* Population::getIndividual(int id) {
    return populationTree->searchElement((id/10));
}

/**@brief devuelve el arbol de poblacion
 * @return Tree<Subject>*
 */
Tree<Subject>* Population::getPopulationTree(){
    return populationTree;
}

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

/**@brief devuelve el tipo de poblacion
 * @return char
 */
void Population::updateGeneration() {
    (*actualGeneration)++;
}

void Population::killEveryone() {
    for(int i = 1; i <= *populationSize; i++){
        populationTree->searchElement(i)->kill();
    }
}
