//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"
#include "../Algorithms/lifeLaboratory.h"
#include "Terrain.h"

/** Construye una poblacion
 * @param Tree<Subject>* peopleTreeParam: primera generacion
 * @param char populationTypeParam: tipo de poblacion
 */
Population::Population(char populationTypeParam, int* activePopulationsOnManagerParam){
    //Reserva espacios
    activePopulationsOnManager = activePopulationsOnManagerParam;
    populationType = static_cast<char*>(malloc(sizeof(char)));
    populationFitness = static_cast<float*>(malloc(sizeof(float)));
    populationSize = static_cast<int*>(malloc(sizeof(int)));
    actualGeneration = static_cast<int*>(malloc(sizeof(int)));
    populationTree = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    defunct = static_cast<bool*>(malloc(sizeof(bool)));
    reproduction_pthread = 0;
    //Llena espacios
    *populationType = populationTypeParam;
    *populationSize = 0;
    *actualGeneration = 1;
    *populationFitness = 0;
    *defunct = false;
    new(populationTree) Tree<Subject>();
}

/**@brief: libera el espacio utilizado
 */
Population::~Population() {
    free(populationTree);
    free(defunct);
    free(reproduction_pthread);
    free(actualGeneration);
    free(populationSize);
    free(populationFitness);
    free(populationType);// tipo de la poblacion
    activePopulationsOnManager = 0;
}

/**@brief: calcula el fitness
 */
void Population::calculateFitness(){
    (*populationFitness) = 0;
    for (int i = 1; i <= (*populationSize); i++) {
        (*populationFitness) += populationTree->searchElement(i-1)->getFitness();
    }
}

/**@brief: inicia el pthread
 */
void Population::init_pthread(){
    reproduction_pthread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    void* parameter = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(parameter)) PThreadParam(this,NULL);
    pthread_create(reproduction_pthread,NULL,reproductionThread,parameter);
}

/**@brief: inserta un nuevo miembro
 * @param Subject* father: padre del individuo
 * @param Subject* mother: madre del individuo
 * @param Chromosome* chromosome: cromosoma del individuo
 */
void Population::insertNewMember(Subject* father, Subject* mother, Chromosome* chromosome) {
    (*populationSize)++;
    populationTree->insertElement(
            Subject(father, mother, chromosome, (*actualGeneration), (*populationSize)*10 + (*populationType)), (*populationSize)
    );
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

/**@brief mata a todos los sujetos
 */
void Population::killEmAll() {
    for(int i = 1; i <= *populationSize; i++){
        populationTree->searchElement(i)->kill();
    }
}

/**@brief bandera de extincion
 * @return bool
 */
bool Population::isDefunct() {
    return *defunct;
}

/**@brief bandera de extincion
 * @return bool
 */
void Population::exterminate(){
    killEmAll();
    *defunct = true;
    (*activePopulationsOnManager)--;
}

/**Accede al pthread
 * return pthread_t*
 */
pthread_t* Population::get_pthread(){
    return reproduction_pthread;
}

/**@brief elimina el pthread
 */
void Population::delete_pthread(){
    free(reproduction_pthread);
}

/**@brief Metodo del pthread
 * @param void* populationParameter: poblacion
 */
void* reproductionThread(void* parameter){
    //Se obtiene el mutex y la poblacion
    Population* population = static_cast<Population*>(static_cast<PThreadParam*>(parameter)->getExcecutioner());
    //Se crea el laboratorio
    LifeLaboratory* laboratory = static_cast<LifeLaboratory*>(malloc(sizeof(LifeLaboratory)));
    new(laboratory) LifeLaboratory(population);
    //Se crea controlador de tiempo
    struct timespec timeControler;
    timeControler.tv_nsec=0;
    timeControler.tv_sec=1;
    //Primera generacion
    laboratory->createPopulation(100);
    //Loop que se ejecutara mientras la poblacion viva
    int x = 0;
    while(!population->isDefunct()){
        laboratory->createGeneration(SUBJECTS_BY_GENERATION);
        x++;
        if(x==100) population->exterminate();
        nanosleep(&timeControler, NULL);
    }
    population->delete_pthread();
    return 0;
}