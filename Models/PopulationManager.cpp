//
// Created by roberto on 10/05/15.
//

#include "PopulationManager.h"

PopulationManager* PopulationManager::singleton = 0;
pthread_t* PopulationManager::managementThread = 0;
pthread_mutex_t* PopulationManager::mutex = 0;

/**@brief constructor
 * @param int numberOfPopulations: numero de poblaciones a manejar
 */
PopulationManager::PopulationManager(int numberOfPopulations){
    //mutex
    mutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(mutex,NULL);
    //Reserva espacio para el contador de poblaciones
    activePopulations = static_cast<int*>(malloc(sizeof(int)));
    //Inicia el contador de poblaciones
    *(activePopulations) = numberOfPopulations;
    //Reserva espacio para el ID de poblaciones
    actualID = static_cast<int*>(malloc(sizeof(int)));
    //Inicia el ID de poblaciones
    *(actualID) = numberOfPopulations;
    //Reserva espacio para N+1 cantidad de poblaciones, donde N = numberOfPopulations
    population = static_cast<Population*>(calloc(0,sizeof(Population)*numberOfPopulations + 1));
    managementThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
}

/**@brief destructor
 */
PopulationManager::~PopulationManager(){
    free(population);
    free(actualID);
    free(managementThread);
    free(activePopulations);
}

/**@brief mezcla las poblaciones para generar una nueva
 * @return Population*
 */
Population* PopulationManager::mergePopulations(){

}

/**@brief metodo que ejecuta las acciones
 */
void PopulationManager::thread() {
    if(trueRandom::getRandom()%RANDOM_WAR_LIMIT < constants::RANDOM_WAR_RANGE_BY_EDDA) {
        //Busca dos numeros random
        int firstPopulationNumber = trueRandom::getRandom()%(INITIAL_NUMBER_OF_POPULATIONS);
        int secondPopulationNumber = trueRandom::getRandom()%(INITIAL_NUMBER_OF_POPULATIONS);
        //Se asegura que no sea la misma poblacion
        while(firstPopulationNumber==secondPopulationNumber) secondPopulationNumber = trueRandom::getRandom()%(INITIAL_NUMBER_OF_POPULATIONS);
        //Se desbloquea mutex
        pthread_mutex_lock(mutex);
        //Inicia las peleas
        for(int i = 0; i < SUBJECTS_BY_GENERATION * 2; i++){
            (*((population+firstPopulationNumber)->getFittest() + i))->setOppenent((*((population+secondPopulationNumber)->getFittest() + i)));
        }
        //Se desbloquea mutex
        pthread_mutex_unlock(mutex);
    }
}

/**@brief devuelve true si hay personas vivas
 * @return bool
 */
bool PopulationManager::isSomeoneAlive(){
    return (*activePopulations > 0);
}

/**@brief accede a las poblaciones actuales
 * @return Population*
 */
Population* PopulationManager::getPopulation(){
    return population;
}

/**@brief accede al thread
 * return pthread_t*
 */
pthread_t* PopulationManager::get_pthread(){
    return managementThread;
}

/**@brief metodo singleton
 * @param pthread_mutex_t* mutex: mutex de memoria, solo se utiliza la primera vez
 * @return PopulationManager*
 */
PopulationManager* PopulationManager::getInstance() {
    if(singleton){
        return singleton;
    }else{
        singleton = static_cast<PopulationManager*>(malloc(sizeof(PopulationManager)));
        new(singleton) PopulationManager(INITIAL_NUMBER_OF_POPULATIONS);
        return singleton;
    }
}

/**@brief elimina el pthread
 */
void PopulationManager::delete_pthread(){
    free(managementThread);
}

void PopulationManager::createLife(){
    //Se bloquea mutex
    pthread_mutex_lock(mutex);
    //Se crea ondicion
    pthread_cond_t* condition = static_cast<pthread_cond_t*>(malloc(sizeof(pthread_cond_t)));
    pthread_cond_init(condition,NULL);
    //Itera creando la cantidad de poblaciones solicitada
    for(int i = 0; i < INITIAL_NUMBER_OF_POPULATIONS; i++){
        new(population+i) Population(i,activePopulations);
        (population+i)->init_pthread(condition);
        pthread_cond_wait(condition,mutex);
    }
    //Se borra condicion
    free(condition);
    //Se desbloquea mutex
    pthread_mutex_unlock(mutex);
}

/**@brief mata a todos
 */
void PopulationManager::killEmAll(){
    //Inicia pthread de poblaciones, se asume que al no haber empezado, las poblaciones activas son todas
    for(int i = 0; i < *actualID; i++){
        //Inicia el pthread
        (population+i)->exterminate();
        //Hace que se espere la finalizacion del pthread
        free((population+i)->get_pthread());
        //Disminuye contador
        (*activePopulations)--;
    }
}

/**@brief Thread del manejador de poblaciones
 */
void* populationManagerThread(void* param){
    //Obtiene manager
    PopulationManager* manager = PopulationManager::getInstance();
    //Se crea el controlador de tiempo
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=5;
    manager->createLife();
    //Este while corre hasta que se mueran todos
    while(manager->isSomeoneAlive()){
        //Ejecuta el metodo
        manager->thread();
        //Espera un segundo
        nanosleep(&timeController, NULL);
    }
    manager->delete_pthread();
    return 0;
}