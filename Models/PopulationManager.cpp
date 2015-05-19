//
// Created by roberto on 10/05/15.
//

#include "PopulationManager.h"

PopulationManager* PopulationManager::singleton = 0;
pthread_t* PopulationManager::managementThread = 0;

/**@brief constructor
 * @param int numberOfPopulations: numero de poblaciones a manejar
 */
PopulationManager::PopulationManager(int numberOfPopulations, pthread_mutex_t* mutex){
    //Reserva espacio para el contador de poblaciones
    activePopulations = static_cast<int*>(malloc(sizeof(int)));
    //Inicia el contador de poblaciones
    *(activePopulations) = numberOfPopulations;
    //Reserva espacio para el ID de poblaciones
    actualID = static_cast<int*>(malloc(sizeof(int)));
    //Inicia el ID de poblaciones
    *(actualID) = numberOfPopulations;
    //Reserva espacio para N cantidad de poblaciones, donde N = numberOfPopulations
    population = static_cast<Population*>(malloc(sizeof(Population)*numberOfPopulations));
    //Itera creando la cantidad de poblaciones solicitada
    for(int i = 0; i < numberOfPopulations; i++){
        new(population+i) Population(i,activePopulations);
    }
    //Reserva espacio para parametro de pthread
    void* parameters = malloc(sizeof(PThreadParam));
    //Crea parametro de pthread
    new(static_cast<PThreadParam*>(parameters)) PThreadParam(this,mutex);
    //Reserva espacio para el pthread
    managementThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    //Inicia el pthread
    pthread_create(managementThread,0,populationManagerThread,parameters);
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
void PopulationManager::thread(){
    //TODO: implementar
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

/**@brief accede al numero de poblaciones activas
 * return int
 */
int PopulationManager::getActivePopulations(){
    return *activePopulations;
}

/**@brief accede al numero de poblaciones activas
 * return int
 */
pthread_t* PopulationManager::get_pthread(){
    return managementThread;
}

/**@brief metodo singleton
 * @param pthread_mutex_t* mutex: mutex de memoria, solo se utiliza la primera vez
 * @return PopulationManager*
 */
PopulationManager* PopulationManager::getInstance(pthread_mutex_t* mutex) {
    if(singleton){
        return singleton;
    }else{
        singleton = static_cast<PopulationManager*>(malloc(sizeof(PopulationManager)));
        new(singleton) PopulationManager(INITIAL_NUMBER_OF_POPULATIONS,mutex);
        return singleton;
    }
}

/**@brief elimina el pthread
 */
void PopulationManager::delete_pthread(){
    free(managementThread);
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
    //Extrae el parametro
    PopulationManager* manager = static_cast<PopulationManager*>(static_cast<PThreadParam*>(param)->getExcecutioner());
    pthread_mutex_t* mutex = static_cast<PThreadParam*>(param)->getMutex();
    //Se crea el controlador de tiempo
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=10;
    //Se desbloquea mutex
    pthread_mutex_lock(mutex);
    //Inicia pthread de poblaciones, se asume que al no haber empezado, las poblaciones activas son todas
    for(int i = 0; i < manager->getActivePopulations(); i++){
        //Inicia el pthread
        (manager->getPopulation()+i)->init_pthread();
    }
    //Este while corre hasta que se mueran todos
    while(manager->isSomeoneAlive()){
        //Llama al metodo del thread
        manager->thread();
        //Espera un segundo
        nanosleep(&timeController, 0);
    }
    //Se desbloquea mutex
    pthread_mutex_unlock(mutex);
    manager->delete_pthread();
    return 0;
}