//
// Created by roberto on 01/05/15.
//

#include "lifeLaboratory.h"

/**@brief: Analiza una lista de sujetos para encontrar coincidencias.
 *         Si el parametro se encuentra en la lista retorna true
 * @param Subject* toSearch: sujeto a buscar en la lista
 * @param DoubleList<Subject*> toAnalyze: lista a analizar
 * @return bool
 */
bool LifeLaboratory::checkSeleccions(Subject* toSearch, DoubleList<Subject*> toAnalyze){
    //Evalua los elementos
    for(int i = 0; i<toAnalyze.len(); i++){
        //(*toAnalyze.get(i)) se desreferencia porque es un DoubleList<Subject*>
        //y el metodo get(int) devuelve T*, es decir, devolvera Subject**
        if((*toAnalyze.get(i)) == toSearch) return true;
    }
    return false;
}

/**@brief: analiza dos cromosomas y retorna el mas fuerte
 * @param Chromosome* firstSon: primer cromosoma
 * @param Chromosome* secondSon: segundo cromosoma
 * @return Chromosome*
 */
Chromosome* LifeLaboratory::selectChromosome(Chromosome* firstSon,Chromosome* secondSon){
    //Inicializa el calculador
    GeneralFitnessCalculator* gfCalculator = static_cast<GeneralFitnessCalculator*>(malloc(sizeof(GeneralFitnessCalculator)));
    new(gfCalculator) GeneralFitnessCalculator();
    //Calcula ambos fitness y retorna el cromosoma ganador, de ser iguales retorna el primero
    if(gfCalculator->calculateFitness(firstSon) >= gfCalculator->calculateFitness(secondSon)){
        free(gfCalculator);
        return firstSon;
    }else{
        free(gfCalculator);
        return secondSon;
    }
}

/** @brief: selecciona dos padres random que superen el fitness medio
 * @param Population* population: poblacion en la cual se realiza la busqueda
 * @param
 * @return Subject*: puntero al espacio de memoria con los dos padres
 */
void LifeLaboratory::selectParents(Population* population, DoubleList<Subject*> parents){
    //Accede al arbol de poblacion y al fitness promedio
    trueRandom::init();
    Tree<Subject>* populationTree = population->getPopulationTree();
    float averageFitness = population->getPopulationFitness() / population->getPopulationSize();

    //Selecciona dos padres
    for(int i = 0; i < 2; i++){
        //Busca hasta que encuentra un sujeto
        for(Subject* toEvaluate = populationTree->searchElement(trueRandom::getRandom()%population->getPopulationSize());
            toEvaluate != 0;
            toEvaluate = populationTree->searchElement(trueRandom::getRandom()%population->getPopulationSize()))
        {
            //Revisa que el individuo este vivo, supere la media de fitness y no haya sido elegido en esta reproduccion
            if(toEvaluate->isAlive() && toEvaluate->getFitness() >= averageFitness
               && !checkSeleccions(toEvaluate, parents))
            {
                parents.append(toEvaluate);
                break;
            }
        }
    }
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
    //Reserva espacio para N sujetos hijos y crea una lista de punteros a los padres, N = numberOfNewSubjects
    Subject* newGeneration = static_cast<Subject*> (malloc(sizeof(Subject)*numberOfNewSubjects));
    DoubleList<Subject*> parents = DoubleList<Subject*>();
    //Llena la nueva generacion
    for (int i = 0; i < numberOfNewSubjects; i++) {
        //Busca padres
        selectParents(population, parents);
        //Reserva espacio para los cromosomas resultantes
        Chromosome* optionsToReproduce = static_cast<Chromosome*>(malloc(2*sizeof(Chromosome)));
        //Toma los padres
        Chromosome* father = (*parents.get(2*i))->getGeneticInformation();
        Chromosome* mother = (*parents.get(2*i+1))->getGeneticInformation();
        //Mezcla cromosomas
        ChromosomeMixer::mix(father,mother, optionsToReproduce);
        //Evalua cromosomas
        Chromosome* luckyChromosome = selectChromosome(optionsToReproduce,optionsToReproduce+sizeof(Chromosome));
        //Crea el nuevo sujeto
        //population->insertNewMember(parents,luckyChromosome);
    }
}