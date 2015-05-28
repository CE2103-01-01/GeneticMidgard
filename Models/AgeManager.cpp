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
    //Edda actual
    years = static_cast<int*>(malloc(sizeof(int)));
    *years = 0;
    //Thread de manejo de eddas
    managementThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    //Mutex
    generalMutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(generalMutex,NULL);
    condition = static_cast<pthread_cond_t*>(malloc(sizeof(pthread_cond_t)));
    pthread_cond_init(condition,NULL);
    //new(objectManager) movilObjectManager();
    pthread_create(managementThread,0,ageManagerThread, static_cast<void*>(this));
    pthread_join(*managementThread,NULL);
}

/**Destructor
 */
AgeManager::~AgeManager(){
    //free(actualAge);
}

/**@brief metodo del thread que evalua las eddas
 */
void AgeManager::thread(){
    evaluateEvolution();
    (*years)++;
}

/**@brief evalua una condicion en un sujeto
 *
 */
bool AgeManager::evaluateSubject(Subject* toEvaluate){
    if(*actualAge==0 && toEvaluate->getGeneticInformation()->getGene(POSITION_OF_GENE_SUPERSTITION) < LIMIT_LEVEL_TWO){
        return false;
    }else if(*actualAge==1 && toEvaluate->getGeneticInformation()->getGene(POSITION_OF_GENE_INTELLIGENCE) < LIMIT_LEVEL_ONE){
        return false;
    }else if(*actualAge==2 && toEvaluate->getGeneticInformation()->getGene(POSITION_OF_GENE_INTELLIGENCE) < LIMIT_LEVEL_TWO){
        return false;
    }else if(*actualAge==3){
        for(int i = 0; i < constantsSubjectXML::NUMBER_OF_GENES - 3; i++){
            if(toEvaluate->getGeneticInformation()->getGene(i) < LIMIT_LEVEL_TWO) return false;
        }
    }else if(*actualAge==4){
        for(int i = 0; i < constantsSubjectXML::NUMBER_OF_GENES - 3; i++){
            if(toEvaluate->getGeneticInformation()->getGene(i) < LIMIT_LEVEL_THREE) return false;
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
    for(int i = 0; i < PopulationManager::getInstance()->getActualID(); i++){
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
    if(!flag | *years > MAX_YEARS) changeAge();
}

/**@brief accede al mutex general
 * @return pthread_mutex_t*
 */
pthread_mutex_t* AgeManager::getGeneralMutex(){
    return generalMutex;
}

/**@brief accede a la condicion general
 * @return pthread_cond_t*
 */
pthread_cond_t* AgeManager::getGeneralCondition(){
    return condition;
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
    (*actualAge)++;
    (*years) = 0;
    //Comprueba en que edda se encuentra
    if(*actualAge < UNION_AGE){
        //Cambia la edda en el calculador de fitness
        GeneralFitnessCalculator::getInstance()->changeEdda();
        showSubjectsByAge();
    }else if(*actualAge == UNION_AGE){
        //Cambia la edda en el calculador de fitness
        GeneralFitnessCalculator::getInstance()->changeEdda();
        //En la edda de la union mezcla las poblaciones
        PopulationManager::getInstance()->mergePopulations();
    }else if(*actualAge == TWILIGHT_OF_THE_GODS_AGE){
        //En la edda de la pelea contra los dioses genera la pelea
        std::cout<< "SE HA ALCANZADO LA META" <<std::endl;
        for(int i = 0; i < INITIAL_NUMBER_OF_POPULATIONS; i++){
            (PopulationManager::getInstance()->getPopulation()+i)->exterminate();
        }
    }
}

void AgeManager::initPopulationManager(){
    //Crea parametro de pthread
    void* populationManagerThreadParameters = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(populationManagerThreadParameters)) PThreadParam(NULL,generalMutex,condition);
    //Inicia el pthread del manejador de poblaciomnes
    pthread_create(PopulationManager::getInstance()->get_pthread(),NULL,populationManagerThread,populationManagerThreadParameters);
    pthread_cond_wait(condition,generalMutex);
}

void AgeManager::showSubjectsByAge()
{
    for(int i = 0; i < INITIAL_NUMBER_OF_POPULATIONS; i++)
    {
        Subject* tmpsubject1 = *((PopulationManager::getInstance()->getPopulation()+i)->getFittest());
        Subject* tmpsubject2 = *((PopulationManager::getInstance()->getPopulation()+i)->getFittest() + INITIAL_NUMBER_OF_SUBJECTS - 1);
        std::cout << "EL SUJETO CON MEJOR FITNES EN LA ERA " << *actualAge - 1<< " EN LA POBLACION "<< tmpsubject1->getID()%SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID << std::endl;
        tmpsubject1->makeSubjectFile();
        tmpsubject1->readSubjectFIle();
        std::cout << "EL SUJETO CON PEOR FITNES EN LA ERA " << *actualAge - 1<< " EN LA POBLACION "<< tmpsubject2->getID()%SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID << std::endl;
        tmpsubject2->makeSubjectFile();
        tmpsubject2->readSubjectFIle();
        std::cout<<""<<std::endl;
    }
    std::cout<< "---------------------------Change Age------------------------"<<std::endl;
    std::cout<<""<<std::endl;
}

/**@brief pthread del manejador de eddas
 */
void* ageManagerThread(void* parameter){
    //Extrae el parametro
    AgeManager* excecutioner = static_cast<AgeManager*>(parameter);
    //Inicializa el manager de poblacion
    excecutioner->initPopulationManager();
    //Ejecute metodo del thread
    while(PopulationManager::getInstance()->getActivePopulations() > 0){
        pthread_cond_wait(excecutioner->getGeneralCondition(),excecutioner->getGeneralMutex());
        excecutioner->thread();
    }
    //Desbloquea mutex
    excecutioner->delete_p_thread();
    return NULL;
}

/**@brief solicita cada cierto tiempo un id para imprimir
 * @param void* PTHREAD_PARAM
 */
void* subjectPrinter(void* parameter){
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=1;
    while(PopulationManager::getInstance()->getActivePopulations() > 0){
        //Crea y lee de consola el id de sujeto
        std::cout << ID_REQUEST << std::endl;
        std::string idToPrintStr;
        std::cin >> idToPrintStr;
        //Convierte el id y lo separa en id de nacimiento e id de poblacion
        long populationID = atol(idToPrintStr.c_str())%SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID;
        long birthID = atol(idToPrintStr.c_str())/SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID;
        //Comprueba la validez del id y lo imprime
        if(populationID < PopulationManager::getInstance()->getActualID()){
            if(birthID <= (PopulationManager::getInstance()->getPopulation()+populationID)->getActualID()){
                (PopulationManager::getInstance()->getPopulation()+populationID)->getSubject(birthID)->print();
            }else{
                std::cout << SUBJECT_ID_ERROR_MESSAGE << std::endl;
            }
        }else{
            std::cout << POPULATION_ID_ERROR_MESSAGE << std::endl;
        }
        nanosleep(&timeController,NULL);
    }
}

