//
// Created by roberto on 01/05/15.
//

#include "lifeLaboratory.h"

/**Constructor
 */
LifeLaboratory::LifeLaboratory(Population* labRatsParam){
    labRats = labRatsParam;
}

/**Constructor
 */
LifeLaboratory::LifeLaboratory(const LifeLaboratory& other){
    labRats = other.labRats;
}

/**Destructor
 */
LifeLaboratory::~LifeLaboratory(){
    labRats = 0;
}

/**@brief: genera un arbol de poblacion
 * @param int populationSize: cantidad de individuos
 * @param int populationNumber: numero de poblacion
 * @return Tree<Subject>*
 */
void LifeLaboratory::createPopulation() {
    for (int i = 0; i < INITIAL_NUMBER_OF_SUBJECTS; i++) {
        //Creael sujeto
        labRats->createNewRandomMember();
    }
    labRats->fillFittest(0);
}

/** Metodo que llena una nueva generacion
 * @param Tree* labRats: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param DoubleList<Subject> parents: la lista de padres
 */
void LifeLaboratory::fillGeneration() {
    //Extrae los mejores
    Subject** parents = labRats->getFittest();
    //Itera creando los sujetos
    for (int i = 0; i < SUBJECTS_BY_GENERATION; i++) {
        //Crea el nuevo cromosoma
        Subject* father = *(parents + i);
        Subject* mother = *(parents + 2*SUBJECTS_BY_GENERATION - (i + 1));
        Chromosome* luckyChromosome = ChromosomeMixer::mix(father->getGeneticInformation(),mother->getGeneticInformation());
        //Crea el nuevo sujeto
        labRats->insertNewMember(father,mother,luckyChromosome);
    }
}

/** Metodo que genera una nueva generacion
 * @param Tree* labRats: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param int generationNumber: numero de la generacion a crear
 */
void LifeLaboratory::createGeneration(){
    //Actualiza fitness
    labRats->updateFittest();
    //Crea nueva generacion
    fillGeneration();
    //Actualiza numero de generaciones
    labRats->updateGeneration();
}