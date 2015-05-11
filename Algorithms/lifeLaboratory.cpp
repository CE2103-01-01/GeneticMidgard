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
void LifeLaboratory::createPopulation(int populationSize) {
    for (int i = 0; i < populationSize; i++) {
        //Creael sujeto
        labRats->createNewRandomMember();
    }
}

/**@brief: Analiza una lista de sujetos para encontrar coincidencias.
 *         Si el parametro se encuentra en la lista retorna true
 * @param Subject* toSearch: sujeto a buscar en la lista
 * @param DoubleList<Subject> toAnalyze: lista a analizar
 * @return bool
 */
bool LifeLaboratory::checkSeleccions(Subject* toSearch, int* toAnalyze, int numberOfParents){
    //Evalua los elementos
    for(int i = 0; i<numberOfParents; i++){
        if(*(toAnalyze + i) == toSearch->getID()) return true;
    }
    return false;
}

/** @brief: selecciona dos padres random que superen el fitness medio
 * @param Population* labRats: poblacion en la cual se realiza la busqueda
 * @param DoubleList<Subject> parents: lista de punteros para retornar por argumento
 * @param int numberOfParents: numero de padres a crear
 * @return Subject*: puntero al espacio de memoria con los dos padres
 */
void LifeLaboratory::selectParents(int numberOfParents, int* parents){
    //Accede al arbol de poblacion y al fitness promedio
    trueRandom::init();
    Tree<Subject>* populationTree = labRats->getPopulationTree();
    float averageFitness = labRats->getPopulationFitness() / labRats->getPopulationSize();
    //Selecciona dos padres
    for(int i = 0; i < numberOfParents; i++){
        bool found = false;
        //Busca hasta que encuentra un sujeto
        while(!found){
            int random = trueRandom::getRandom()%labRats->getPopulationSize()+1;
            if(random <= labRats->getPopulationSize()){
                Subject* toEvaluate = populationTree->searchElement(random);
                //Revisa que el individuo este vivo, supere la media de fitness y no haya sido elegido en esta reproduccion
                if(toEvaluate!=0 && toEvaluate->isAlive()!=0 && toEvaluate->isAlive() && !checkSeleccions(toEvaluate, parents, i)) {
                    *(parents + i)= toEvaluate->getID();
                    found = true;
                }
            }
        }
    }
}

/** Metodo que llena una nueva generacion
 * @param Tree* labRats: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param DoubleList<Subject> parents: la lista de padres
 */
void LifeLaboratory::fillGeneration(int numberOfNewSubjects, int* parents) {
    //Itera creando los sujetos
    for (int i = 0; i < numberOfNewSubjects; i++) {
        //Crea el nuevo cromosoma
        Subject* father = labRats->getIndividual(*(parents+2*i));
        Subject* mother = labRats->getIndividual(*(parents+2*i+1));
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
void LifeLaboratory::createGeneration(int numberOfNewSubjects){
    //Crea una lista de punteros a los padres
    int* parents = static_cast<int*>(malloc(sizeof(int) * numberOfNewSubjects));
    selectParents(2*numberOfNewSubjects, parents);
    //Genera los hijos
    fillGeneration(numberOfNewSubjects, parents);
    //Actualiza numero de generaciones
    labRats->updateGeneration();
}