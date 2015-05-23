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
    free(actualAge);
}

/**@brief metodo del thread que evalua las eddas
 */
void AgeManager::thread(){
    pthread_mutex_lock(generalMutex);
    evaluateEvolution();
    pthread_mutex_unlock(generalMutex);
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
        Population* tmpPopulation = PopulationManager::getInstance()->getPopulation() + i;
        //Se pregunta si la poblacion tomada no es vacia ni extinta
        if(!tmpPopulation->isDefunct()){
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

/**@brief elimina el pthread y mutex
 */
void AgeManager::delete_p_thread(){
    free(managementThread);
    free(generalMutex);
}

/**@brief cambia el calculo de fitness
 */
void AgeManager::changeAge(){
    //Cambia la edda en el calculador de fitness
    GeneralFitnessCalculator::getInstance()->changeEdda();
    //Comprueba en que edda se encuentra
    if(*actualAge == UNION_AGE){
        //En la edda de la union mezcla las poblaciones
        PopulationManager::getInstance()->mergePopulations();
    }else if(*actualAge == TWILIGHT_OF_THE_GODS_AGE){
        //En la edda de la pelea contra los dioses genera la pelea
        std::cout<< "Se ha alcanzado la meta" <<std::endl;
        (PopulationManager::getInstance()->getPopulation()+INITIAL_NUMBER_OF_POPULATIONS+1)->exterminate();
    }
}

void AgeManager::initPopulationManager(){
    //Se crea condicion
    pthread_cond_t* condition = static_cast<pthread_cond_t*>(malloc(sizeof(pthread_cond_t)));
    pthread_cond_init(condition,NULL);
    //Crea parametro de pthread
    void* populationManagerThreadParameters = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(populationManagerThreadParameters)) PThreadParam(NULL,NULL,condition);
    //Inicia el pthread del manejador de poblaciomnes
    pthread_create(PopulationManager::getInstance()->get_pthread(),NULL,populationManagerThread,populationManagerThreadParameters);
    pthread_cond_wait(condition,generalMutex);
}

/**@brief pthread del manejador de eddas
 */
void* ageManagerThread(void* parameter){
    AgeManager* excecutioner = static_cast<AgeManager*>(parameter);

    //Se crea el controlador de tiempo
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=100;

    excecutioner->initPopulationManager();

    //Ejecuta el metodo del hilo hasta que esten todos extintos
    while(PopulationManager::getInstance()->getActivePopulations() > 0){
        excecutioner->thread();
        //Espera cien segundos
        nanosleep(&timeController, NULL);
    }
    PopulationManager::getInstance()->killEmAll();
    //Borra el thread
    excecutioner->delete_p_thread();
    return NULL;
}