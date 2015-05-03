//
// Created by roberto on 01/05/15.
//

#include "lifeLaboratory.h"

LifeLaboratory::LifeLaboratory(pthread_mutex_t* mutexParam){
    mutex = mutexParam;
}

/**@brief: genera un arbol de poblacion
 * @param int populationSize: cantidad de individuos
 * @param int populationNumber: numero de poblacion
 * @return Tree<Subject>*
 */
Tree<Subject> LifeLaboratory::createPopulation(int populationSize, int populationNumber) {
    //Reserva espacio para el arbol
    Tree<Subject> toReturn = Tree<Subject>(TREE_SIZE);
    for (int i = 0; i < populationSize; i++) {
        //Crea un sujeto, si es sujeto numero 3 de poblacion 5, su id sera 35 y estara en posicion 3
        //Introduce el sujeto
        toReturn.insertElement(Subject((i+1)*10 + populationNumber));
    }
    return toReturn;
}

/**@brief: Analiza una lista de sujetos para encontrar coincidencias.
 *         Si el parametro se encuentra en la lista retorna true
 * @param Subject* toSearch: sujeto a buscar en la lista
 * @param DoubleList<Subject> toAnalyze: lista a analizar
 * @return bool
 */
bool LifeLaboratory::checkSeleccions(Subject* toSearch, DoubleList<Subject>* toAnalyze){
    //Evalua los elementos
    for(int i = 0; i<toAnalyze->len(); i++){
        if((toAnalyze->get(i)) == toSearch) return true;
    }
    return false;
}

/**@brief: analiza dos cromosomas y retorna el mas fuerte
 * @param Chromosome* firstSon: primer cromosoma
 * @param Chromosome* secondSon: segundo cromosoma
 * @return Chromosome*
 */
Chromosome* LifeLaboratory::selectChromosome(Chromosome* sons){
    //Inicializa el calculador
    GeneralFitnessCalculator* gfCalculator = static_cast<GeneralFitnessCalculator*>(malloc(sizeof(GeneralFitnessCalculator)));
    new(gfCalculator) GeneralFitnessCalculator();
    //Calcula ambos fitness y retorna el cromosoma ganador, de ser iguales retorna el primero
    if(gfCalculator->calculateFitness(sons) >= gfCalculator->calculateFitness(sons+sizeof(Chromosome))){
        free(gfCalculator);
        return sons;
    }else{
        free(gfCalculator);
        return sons+sizeof(Chromosome);
    }
}

/** @brief: selecciona dos padres random que superen el fitness medio
 * @param Population* population: poblacion en la cual se realiza la busqueda
 * @param DoubleList<Subject> parents: lista de punteros para retornar por argumento
 * @param int numberOfParents: numero de padres a crear
 * @return Subject*: puntero al espacio de memoria con los dos padres
 */
DoubleList<Subject>* LifeLaboratory::selectParents(Population* population, int numberOfParents){
    //Accede al arbol de poblacion y al fitness promedio
    DoubleList<Subject>* parents = static_cast<DoubleList<Subject>*>(malloc(sizeof(DoubleList<Subject>)));
    new(parents) DoubleList<Subject>();
    trueRandom::init();
    Tree<Subject>* populationTree = population->getPopulationTree();
    float averageFitness = population->getPopulationFitness() / population->getPopulationSize();
    //Selecciona dos padres
    for(int i = 0; i < numberOfParents; i++){
        bool found = false;
        //Busca hasta que encuentra un sujeto
        for(int random = trueRandom::getRandom()%population->getPopulationSize();
            !found;
            random = trueRandom::getRandom()%population->getPopulationSize())
        {
            if(random < population->getPopulationSize()){
                Subject* toEvaluate = populationTree->searchElement(random);
                //Revisa que el individuo este vivo, supere la media de fitness y no haya sido elegido en esta reproduccion
                if(toEvaluate!=0 && toEvaluate->isAlive() && !checkSeleccions(toEvaluate, parents))
                {
                    parents->append(toEvaluate);
                    found = true;
                }
            }
        }
    }
    return parents;
}

/** Metodo que llena una nueva generacion
 * @param Tree* population: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param DoubleList<Subject> parents: la lista de padres
 */
void LifeLaboratory::fillGeneration(Population *population, int numberOfNewSubjects, DoubleList<Subject>* parents) {
    //Itera creando los sujetos
    for (int i = 0; i < numberOfNewSubjects; i++) {
        std::cout << "INDICE DEL METODO FILL GENERATION: " << i << std::endl;
        //Reserva espacio para los cromosomas resultantes
        Chromosome* newChromosomes = static_cast<Chromosome*>(malloc(2*sizeof(Chromosome)));
        //Mezcla cromosomas
        ChromosomeMixer::mix(parents->get(2*i)->getGeneticInformation(),
                             parents->get(2*i+1)->getGeneticInformation(),
                             newChromosomes);
        std::cout<< "CANTIDAD DE GENES CROMOSOMA 1: " << (newChromosomes)->getNumberOfGenes()  <<std::endl;
        std::cout<< "CANTIDAD DE GENES CROMOSOMA 2: " << (newChromosomes + sizeof(Chromosome))->getNumberOfGenes() <<std::endl;
        //Evalua cromosomas
        Chromosome* luckyChromosome = selectChromosome(newChromosomes);
        //Crea el nuevo sujeto
        population->insertNewMember((parents->get(2*i)),(parents->get(2*i+1)),luckyChromosome);
    }
}

/** Metodo que genera una nueva generacion
 * @param Tree* population: poblacion a analizar
 * @param int numberOfNewSubjects: numero de sujetos a generar
 * @param int generationNumber: numero de la generacion a crear
 */
void LifeLaboratory::createGeneration(Population* population, int numberOfNewSubjects){
    //Crea una lista de punteros a los padres
    DoubleList<Subject>* parents = selectParents(population, 2*numberOfNewSubjects);
    //Genera los hijos
    fillGeneration(population, numberOfNewSubjects, parents);
    //Actualiza numero de generaciones
    population->updateGeneration();
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
        Tree<Subject> people = createPopulation(populationSize,i);
        //Llena una poblacion
        new (toReturn + i*sizeof(Population)) Population(people, static_cast<char>(i), populationSize);
    }
    std::cout << "POPULATION CREATED" << std::endl;
    return toReturn;
}