//
// Created by roberto on 10/05/15.
//

#include "PopulationManager.h"
#include "../Algorithms/lifeLaboratory.h"
#include "God.h"

PopulationManager* PopulationManager::singleton = 0;
pthread_t* PopulationManager::managementThread = 0;
pthread_t* PopulationManager::warThread = 0;
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
    *(activePopulations) = INITIAL_NUMBER_OF_POPULATIONS;
    //Reserva espacio para el ID de poblaciones
    actualID = static_cast<int*>(malloc(sizeof(int)));
    //Inicia el ID de poblaciones
    *(actualID) = INITIAL_NUMBER_OF_POPULATIONS;
    //Reserva espacio para N+1 cantidad de poblaciones, donde N = numberOfPopulations
    population = static_cast<Population*>(malloc(sizeof(Population)*INITIAL_NUMBER_OF_POPULATIONS + 1));
    managementThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    warThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
}

/**@brief destructor
 */
PopulationManager::~PopulationManager(){
    free(population);
    free(actualID);
    free(activePopulations);
}

/**@brief mezcla las poblaciones para generar una nueva
 * @return Population*
 */
void PopulationManager::mergePopulations(){
    //Se bloquea mutex
    pthread_mutex_lock(mutex);
    new(population + INITIAL_NUMBER_OF_POPULATIONS) Population(INITIAL_NUMBER_OF_POPULATIONS, activePopulations);
    //Se crea tabla de indices que ayuda a saber cual fue el ultimo indice en los fittest que se recorrio
    //asi no se recorren sujetos que ya se incluyeron
    int* index = static_cast<int*>(calloc(0,sizeof(int) * INITIAL_NUMBER_OF_POPULATIONS));
   //Se busca a los mejores
    for(int i=0; i<2*SUBJECTS_BY_GENERATION; i++){
        //Se toma un temporal en la primer poblacion y se compara con los demas
        Subject* tmp = *(population->getFittest() + *index);
        for(int j=1; j<INITIAL_NUMBER_OF_POPULATIONS; j++){
            //Evalua cual tiene mayor fitness
            if((*((population+j)->getFittest() + *(index+j)))->getFitness() > tmp->getFitness()){
                //Si el temporal actual tiene menor fitness lo cambia
                tmp = *((population+j)->getFittest() + *(index+j));
            }
        }
        //Suma uno al indice correspondiente a la poblacion del sujeto
        (*(index + tmp->getID()%10))++;
        //Inserta al sujeto en la nueva poblacion
        (population + INITIAL_NUMBER_OF_POPULATIONS)->insertNewMember(tmp);
    }
    (population + INITIAL_NUMBER_OF_POPULATIONS)->updateFittest();
    //killEmAll();
    (*activePopulations)++;
    (*actualID)++;
}

/**Inicia la guerra
 */
void PopulationManager::init_war(){
    //Busca dos numeros random
    int firstPopulationNumber = trueRandom::getRandom()%(INITIAL_NUMBER_OF_POPULATIONS);
    int secondPopulationNumber = trueRandom::getRandom()%(INITIAL_NUMBER_OF_POPULATIONS);
    //Se asegura que no sea la misma poblacion
    while(firstPopulationNumber==secondPopulationNumber){
        secondPopulationNumber = trueRandom::getRandom()%(INITIAL_NUMBER_OF_POPULATIONS);
    }
    //ultima persona visitada
    int lastDefense = 0;
    //Inicia las peleas
    for(int i = 0; i < 2*SUBJECTS_BY_GENERATION; i++){
        //Toma un sujeto temporal y revisa si es guerrero
        Subject* tmpWarrior = *((population+firstPopulationNumber)->getFittest() + i);
        if(tmpWarrior->getCharacteristic(POSITION_OF_CHARACTERISTIC_PROFESSION)==PROFESSION_WARRIOR && !tmpWarrior->getOpponent()){
            //toma un sujeto temporal para iterta en busca de defensa
            Subject* tmpDefense = 0;
            //Busca un defensa
            for(int j=lastDefense; j<2*SUBJECTS_BY_GENERATION;j++){
                //Si encuentra a un defensa lo coloca en el temporal y actualiza el id
                if((*((population+secondPopulationNumber)->getFittest() + j))
                           ->getCharacteristic(POSITION_OF_CHARACTERISTIC_PROFESSION)==PROFESSION_DEFENSE){
                    tmpDefense=*((population+secondPopulationNumber)->getFittest() + j);
                    lastDefense = j+1;
                }
            }
            //Si el defensa no es nulo lo coloca como oponente, si no corta el ciclo al no haber gente disponible
            if(tmpDefense)tmpWarrior->setOppenent(tmpDefense);
            else break;
        }
    }
}

/**Inicia la ultima guerra
 */
void PopulationManager::initFinalWar(){
    //Se crea el controlador de tiempo
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=10;
    *activePopulations--;
    nanosleep(&timeController, NULL);
    for(int i = 0; i < INITIAL_NUMBER_OF_SUBJECTS; i++){
        //Toma un sujeto y crea un dios temporal
        God* tmpGod = static_cast<God*>(malloc(sizeof(God)));
        new(tmpGod) God();
        Subject* tmpSubject = *((population+INITIAL_NUMBER_OF_POPULATIONS)->getFittest()+i);
        //Toma las caracteristicas de interes
        unsigned char tmpGodAttack = tmpGod->getAttribute(POSITION_OF_GOD_ATTRIBUTE_ATTACK);
        unsigned char tmpGodDefense = tmpGod->getAttribute(POSITION_OF_GOD_ATTRIBUTE_DEFENSE);
        unsigned char tmpSubjectAttack = tmpSubject->getGeneticInformation()->getGene(POSITION_OF_GENE_ATTACK);
        unsigned char tmpSubjectDefense = tmpSubject->getGeneticInformation()->getGene(POSITION_OF_GENE_DEFENSE);
        //Itera hasta que alguno muera
        while(tmpGod->isAlive() && tmpSubject->isAlive()){
            //Tira moneda al aire
            int coin = trueRandom::getRandom()%(tmpGodAttack+tmpSubjectAttack);
            //Si es menor que el ataque del dios, ataca el dios
            if(coin<tmpGodAttack){
                //Si el ataque es mayor, acierta
                if(tmpGodAttack>tmpSubjectDefense) {
                    tmpSubject->setCharacteristic(POSITION_OF_CHARACTERISTIC_LIFE,tmpSubjectDefense-tmpGodAttack);
                }//Si el ataque es igual que la defensa, ambos golpean
                else if(tmpGodAttack==tmpSubjectDefense){
                    tmpSubject->setCharacteristic(POSITION_OF_CHARACTERISTIC_LIFE,-tmpGodAttack);
                    tmpGod->decreseLife(tmpSubjectDefense);
                }//Si el ataque es menor  que la defensa, lo golpean
                else{
                    tmpGod->decreseLife(tmpSubjectDefense-tmpGodAttack);
                }
            }//Si es mayor que el ataque del dios, ataca el sujeto
            else{
                //Si el ataque es mayor que la defensa, acierta
                if(tmpSubjectAttack>tmpGodDefense) {
                    tmpGod->decreseLife(tmpSubjectAttack-tmpGodDefense);
                }//Si el ataque es igual que la defensa, ambos golpean
                else if(tmpSubjectAttack==tmpGodDefense){
                    tmpSubject->setCharacteristic(POSITION_OF_CHARACTERISTIC_LIFE,-tmpGodDefense);
                    tmpGod->decreseLife(tmpSubjectAttack);
                }//Si el ataque es menor que la defensa, lo golpean
                else{
                    tmpSubject->setCharacteristic(POSITION_OF_CHARACTERISTIC_LIFE,tmpSubjectAttack-tmpGodDefense);
                }
            }
        }
        //Libera espacio
        free(tmpGod);
    }
}

/**Reproduce a las poblaciones
 */
void PopulationManager::reproduce(){
   for(int i = 0; i < *actualID; i++){
        if(!(population+i)->isDefunct()){
            LifeLaboratory* laboratory = static_cast<LifeLaboratory*>(malloc(sizeof(LifeLaboratory)));
            new(laboratory) LifeLaboratory((population+i));
            //Primera generacion
            laboratory->createGeneration();
            free(laboratory);
        }
   }
}

/**@brief metodo que ejecuta las acciones
 */
void PopulationManager::thread() {
    if(trueRandom::getRandom()%RANDOM_WAR_LIMIT < constants::RANDOM_WAR_RANGE_BY_EDDA && *activePopulations>1) init_war();
}

/**@brief devuelve true si hay personas vivas
 * @return bool
 */
bool PopulationManager::isSomeoneAlive(){
    return (*activePopulations > 0);
}

/**@brief devuelve el id actual
 * @return int
 */
int PopulationManager::getActualID(){
    return *actualID;
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

/**@brief accede al thread
 * return pthread_t*
 */
pthread_t* PopulationManager::get_war_pthread(){
    return warThread;
}

/**@brief accede al thread
 * return pthread_t*
 */
int PopulationManager::getActivePopulations(){
    return *activePopulations;
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
/**@brief elimina el pthread
 */
void PopulationManager::delete_war_pthread(){
    free(warThread);
}
/**Inicia pthread de poblaiciones, se asume que al no haber empezado, las poblaciones activas son todas
 */
void PopulationManager::createLife(){
    //Itera creando la cantidad de poblaciones solicitada
    for(int i = 0; i < INITIAL_NUMBER_OF_POPULATIONS; i++){
        new(population+i) Population(i,activePopulations);
        LifeLaboratory* laboratory = static_cast<LifeLaboratory*>(malloc(sizeof(LifeLaboratory)));
        new(laboratory) LifeLaboratory(population+i);
        //Primera generacion
        laboratory->createPopulation();
        free(laboratory);
    }
}

/**@brief mata a todos
 */
void PopulationManager::killEmAll(){
    for(int i = 0; i < *actualID; i++){
        if(!(population+i)->isDefunct()){
            //Inicia el pthread
            (population+i)->exterminate();
            //Disminuye contador
            (*activePopulations)--;
        }
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
    pthread_mutex_lock(static_cast<PThreadParam*>(param)->getMutex());
    manager->createLife();
    pthread_cond_signal(static_cast<PThreadParam*>(param)->getCondition());
    pthread_mutex_unlock(static_cast<PThreadParam*>(param)->getMutex());
    //Este while corre hasta que se mueran todos
    while(manager->isSomeoneAlive()){
        //pthread_mutex_lock(static_cast<PThreadParam*>(param)->getMutex());
        //Ejecuta el metodo
        manager->reproduce();
        pthread_cond_signal(static_cast<PThreadParam*>(param)->getCondition());
        //pthread_mutex_unlock(static_cast<PThreadParam*>(param)->getMutex());
        //Espera un segundo
        nanosleep(&timeController, NULL);
    }
    return 0;
}

/**@brief Thread del manejador de poblaciones
 */
void* populationManagerWarThread(void* param){
    //Obtiene manager
    PopulationManager* manager = PopulationManager::getInstance();
    //Se crea el controlador de tiempo
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=5;
    //Este while corre hasta que se mueran todos
    while(constants::RANDOM_WAR_RANGE_BY_EDDA){
        //Ejecuta el metodo
        manager->thread();
        //Espera un segundo
        nanosleep(&timeController, NULL);
    }
    return 0;
}