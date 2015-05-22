//
// Created by roberto on 10/05/15.
//

#include "AgeManager.h"

/**Constructor
 */
AgeManager::AgeManager(){
    //Edda actual
    actualAge = static_cast<int*>(malloc(sizeof(int)));
    *actualAge = 0;
    //Sleep general
    generalSleep = static_cast<long*>(malloc(sizeof(long)));
    *generalSleep = 1000;
    //Thread de manejo de eddas
    managementThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    //Mutex
    generalMutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(generalMutex,NULL);
    //Manejador de objetos moviles
    //objectManager = static_cast<movilObjectManager*>(malloc(sizeof(movilObjectManager)));
    //new(objectManager) movilObjectManager();
    pthread_create(managementThread,0,ageManagerThread, static_cast<void*>(this));
    pthread_join(*managementThread,NULL);
}

/**Destructor
 */
AgeManager::~AgeManager(){
    free(generalMutex);
    free(generalSleep);
    free(managementThread);
    free(populationManager);
 //   free(objectManager);
    free(actualAge);
}

void AgeManager::thread(){

}

/**@brief evalua una condicion en un sujeto
 *
 */
bool AgeManager::evaluateSubject(Subject* toEvaluate){
    switch(*actualAge){
        case 0:
            if(toEvaluate->getGeneticInformation()->getGene(POSITION_OF_GENE_SUPERSTITION) <= LIMIT_LEVEL_THREE) return false;
        case 1:
            if(toEvaluate->getGeneticInformation()->getGene(POSITION_OF_GENE_INTELLIGENCE) <= LIMIT_LEVEL_ONE) return false;
        case 2:
            if(toEvaluate->getGeneticInformation()->getGene(POSITION_OF_GENE_INTELLIGENCE) <= LIMIT_LEVEL_THREE) return false;
        case 3:
            for(int i = 0; i < constantsSubjectXML::NUMBER_OF_GENES - 3; i++){
                if(toEvaluate->getGeneticInformation()->getGene(i) <= LIMIT_LEVEL_TWO) return false;
            }
        case 4:
            for(int i = 0; i < constantsSubjectXML::NUMBER_OF_GENES - 3; i++){
                if(toEvaluate->getGeneticInformation()->getGene(i) <= LIMIT_LEVEL_THREE) return false;
            }
    }
    return true;
}

/**@brief evalua una condicion en los mejores miembros de las poblaciones, si se cumple en todos la edda cambia
 */
void AgeManager::evaluateEvolution(){
    //bandera que corta el ciclo
    bool flag = false;
    //Itera en las poblaciones
    for(int i = 0; i < INITIAL_NUMBER_OF_POPULATIONS + 1; i++){
        //poblacion
        Population* tmpPopulation = populationManager->getPopulation() + i;
        //Se pregunta si la poblacion tomada no es vacia ni extinta
        if(static_cast<unsigned char*>(static_cast<void*>(tmpPopulation))!=0 && !tmpPopulation->isDefunct()){
            //Se revisa a los mejores
            for(int i = 0; i < 2 * SUBJECTS_BY_GENERATION; i++){
                //Si alguno no cumple se cortan ambos ciclos
                if(!evaluateSubject(*(tmpPopulation->getFittest()+i))){
                    flag = true;
                    break;
                }
            }
        }
        //Si no se cumplio se finaliza
        if(flag) break;
    }
    //Si se cumplio el parametro cambia la edda
    if(!flag) changeAge();
}

/**@brief accede al mutex general
 * @return pthread_mutex_t*
 */
pthread_mutex_t* AgeManager::getGeneralMutex(){
    return generalMutex;
}

/**@brief accede al pthread
 * @return pthread_t*
 */
pthread_t* AgeManager::getManagementThread(){
    return managementThread;
}

/**@brief accede al manejador de poblaciones
 * @return PopulationManager*
 */
PopulationManager* AgeManager::getPopulationManager(){
    return populationManager;
}

/**@brief accede al manejador de objetos
 * @return movilObjectManager*
 */
movilObjectManager* AgeManager::getMovilObjectManager(){
    return objectManager;
}

/**@brief accede al sleep general
 * @return long
 */
long AgeManager::getGeneralSleep(){
    return *generalSleep;
}

/**@brief accede a la edda actual
 * @return int
 */
int AgeManager::getActualAge(){
    return *actualAge;
}

/**@brief cambia el calculo de fitness
 */
void AgeManager::changeAge(){
    GeneralFitnessCalculator::getInstance()->changeEdda();
}

void* ageManagerThread(void* parameter){
    AgeManager* excecutioner = static_cast<AgeManager*>(parameter);
    //Reserva espacio para parametro de pthread
    PopulationManager* manager = PopulationManager::getInstance();
    void* populationManagerThreadParameters = malloc(sizeof(PThreadParam));
    //Crea parametro de pthread
    new(static_cast<PThreadParam*>(populationManagerThreadParameters))
            PThreadParam(NULL,excecutioner->getGeneralMutex(),NULL);
    //Inicia el pthread del manejador de poblaciomnes
    pthread_create(manager->get_pthread(),NULL,populationManagerThread,populationManagerThreadParameters);
    pthread_join(*(manager->get_pthread()),0);


    return NULL;
}