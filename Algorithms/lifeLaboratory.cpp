//
// Created by roberto on 01/05/15.
//

#include "lifeLaboratory.h"

/**Constructor
 */
LifeLaboratory::LifeLaboratory(Population* populationParam){
    population = populationParam;
}

/**Constructor
 */
LifeLaboratory::LifeLaboratory(const LifeLaboratory& other){
    population = other.population;
}

/**Destructor
 */
LifeLaboratory::~LifeLaboratory(){
    population = 0;
}

/**@brief: genera un arbol de poblacion
 * @param int populationSize: cantidad de individuos
 * @param int populationNumber: numero de poblacion
 * @return Tree<Subject>*
 */
void LifeLaboratory::createPopulation() {
    for (int i = 0; i < INITIAL_NUMBER_OF_SUBJECTS; i++) {
        //Creael sujeto
        population->createNewRandomMember();
    }
    population->fillFittest(NULL);
}

/** Metodo que llena una nueva generacion
 * @param Tree* population: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param DoubleList<Subject> parents: la lista de padres
 */
void LifeLaboratory::fillGeneration() {
    //Extrae los mejores
    Subject** parents = population->getFittest();
    //Itera creando los sujetos
    for (int i = 0; i < SUBJECTS_BY_GENERATION; i++) {
        //Crea el nuevo cromosoma
        Subject* father = *(parents + i);
        Subject* mother = *(parents + 2*SUBJECTS_BY_GENERATION - (i + 1));
        Chromosome* luckyChromosome = ChromosomeMixer::mix(father->getGeneticInformation(),mother->getGeneticInformation());
        //Crea el nuevo sujeto
        population->insertNewMember(father,mother,luckyChromosome);
    }
}

/** Metodo que genera una nueva generacion
 * @param Tree* population: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param int generationNumber: numero de la generacion a crear
 */
void LifeLaboratory::createGeneration(){
    //Actualiza fitness
    population->updateFittest();
    //Crea nueva generacion
    fillGeneration();
    //Actualiza numero de generaciones
    population->updateGeneration();
}