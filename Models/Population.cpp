//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"
#include "../Algorithms/lifeLaboratory.h"
#include "Terrain.h"

/** Construye una poblacion
 * @param Tree<Subject>* peopleTreeParam: primera generacion
 * @param char populationTypeParam: tipo de poblacion
 */
Population::Population(char populationTypeParam, int* activePopulationsOnManagerParam){
    //Reserva espacios
    colors = static_cast<unsigned char*>(malloc(3));
    *(colors) = trueRandom::getRandom()%256;
    *(colors + 1) = trueRandom::getRandom()%256;
    *(colors + 2) = trueRandom::getRandom()%256;
    activePopulationsOnManager = activePopulationsOnManagerParam;
    populationType = static_cast<char*>(malloc(sizeof(char)));
    *populationType = populationTypeParam;
    populationSize = static_cast<int*>(malloc(sizeof(int)));
    *populationSize = 0;
    fittest = static_cast<Subject**>(malloc(sizeof(Subject*) * 2 * SUBJECTS_BY_GENERATION));
    actualGeneration = static_cast<int*>(malloc(sizeof(int)));
    *actualGeneration = 1;
    populationTree = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    new(populationTree) Tree<Subject>();
    defunct = static_cast<bool*>(malloc(sizeof(bool)));
    *defunct = false;
    reproduction_pthread = 0;
    position = static_cast<Vector2D*>(malloc(sizeof(Vector2D)));
    *position = (Terrain::getRandomFreePosition());
}

/**@brief: libera el espacio utilizado
 */
Population::~Population() {
    free(fittest);
    free(colors);
    free(populationTree);
    free(defunct);
    free(reproduction_pthread);
    free(actualGeneration);
    free(populationSize);
    free(populationType);// tipo de la poblacion
    activePopulationsOnManager = 0;
}

/**@brief: inicia el pthread
 */
void Population::init_pthread(pthread_cond_t* managerConditionParam){
    reproduction_pthread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    void* parameter = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(parameter)) PThreadParam(this,NULL,managerConditionParam);
    pthread_create(reproduction_pthread,NULL,reproductionThread,parameter);
}

/**@brief: inserta un nuevo miembro
 * @param Subject* father: padre del individuo
 * @param Subject* mother: madre del individuo
 * @param Chromosome* chromosome: cromosoma del individuo
 */
void Population::insertNewMember(Subject* father, Subject* mother, Chromosome* chromosome) {
    (*populationSize)++;
    populationTree->insertElement(
            Subject(father, mother, chromosome, (*actualGeneration), (*populationSize)*10 + (*populationType),  actualGeneration),
            *populationSize
    );
    Subject* newMember = populationTree->searchElement(*populationSize);
    if(newMember->getFitness() > (*(fittest+2*SUBJECTS_BY_GENERATION-1))->getFitness()) updateFittest(newMember);
    newMember->start_p_thread();
}

/**@brief: inserta un nuevo miembro
 * @param Subject* nuevo miembro
 */
void Population::insertNewMember(Subject* newMemberParam) {
    (*populationSize)++;
    populationTree->insertElement(Subject(*newMemberParam),*populationSize);
    populationTree->searchElement(*populationSize)->start_p_thread();
}

/**@brief: inserta un nuevo miembro random
 */
void Population::createNewRandomMember() {
    (*populationSize)++;
    populationTree->insertElement(Subject((*populationSize)*10 + (*populationType), actualGeneration, colors,Terrain::getRandomFreePositionNear(*position)),*populationSize);
    Subject* newMember = populationTree->searchElement(*populationSize);
    newMember->start_p_thread();
}

/**@brief: inserta un nuevo miembro random
 * @param Subject* newMember: nuevo miembro
 */
void Population::updateFittest(Subject* newMember) {
    //Se ingresa al metodo porque el parametro tiene mayor fitness que el ultimo, por eso se asigna para evitar
    //comparaciones redundantes
    *(fittest+2*SUBJECTS_BY_GENERATION-1) = newMember;
    //Itera acomodando al nuevo miembro en la posicion correspondiente
    for(int i = 2*SUBJECTS_BY_GENERATION-1; i>0; i--){
        //Si el sujeto en i tiene mayor fitness que el de i-1, estan desordenados y se hace un swap
        if((*(fittest+i))->getFitness() > (*(fittest+i-1))->getFitness()){
            //Se crea un temporal con el sujeto en i-1
            Subject* tmp = *(fittest+i-1);
            //Se guarda el sujeto i en el campo i-1
            *(fittest+i-1) = *(fittest+i);
            //Se guarda el temporal en el campo i
            *(fittest+i) = tmp;
        }
    }
}

/**@brief: inserta un nuevo miembro random
 * @param Subject* newMember: nuevo miembro
 */
void Population::updateFittest() {
    int deficit = 0;
    //Itera acomodando al nuevo miembro en la posicion correspondiente
    for(int i = 2*SUBJECTS_BY_GENERATION-1; i>=0; i--){
        //Si un miembro esta muerto
        if(!((*(fittest+i))->isAlive())){
            deficit++;
            for(int j = i+1; j < 2*SUBJECTS_BY_GENERATION-deficit; j++){
                //Se acomoda al muerto al final
                Subject* tmp = *(fittest+j);
                *(fittest+j) = *(fittest+j-1);
                *(fittest+j-1) = tmp;
            }
        }
    }
    fillFittest(2*SUBJECTS_BY_GENERATION - deficit);
}

/**@brief devuelve el tipo de poblacion
 * @return char
 */
void Population::updateGeneration() {
    (*actualGeneration)++;
}

/**@brief mata a todos los sujetos
 */
void Population::killEmAll() {
    for(int i = 1; i <= *populationSize; i++){
        populationTree->searchElement(i)->kill();
    }
}

/**@brief bandera de extincion
 * @return bool
 */
bool Population::isDefunct() {
    return *defunct;
}


/**@brief accede a los mejores
 * @return Subject**
 */
Subject** Population::getFittest() {
    return fittest;
}

/**@brief llena la lista de los mejores seres
 */
void Population::fillFittest(int deficit){
    if(*populationSize > INITIAL_NUMBER_OF_SUBJECTS){
        //Busca la cantidad de padres necesaria con mejor fitness
        for(int i = 0; i < SUBJECTS_BY_GENERATION; i++){
            //Pregunta si esta lleno el espacio de los muertos y compara uno a uno los nuevos sujetos con los mejores
            //Hace cambios si el nacimiento es mejor o hubo muertos
            if(populationTree->searchElement(*populationSize - SUBJECTS_BY_GENERATION+i)->getFitness()
               >= (*(fittest + 2*SUBJECTS_BY_GENERATION-1))->getFitness() | i < deficit) {
                //Mata al menor
                (*(fittest + 2*SUBJECTS_BY_GENERATION-1))->kill();
                //Coloca al nuevo mejor en el lugar del muerto
                (*(fittest + 2*SUBJECTS_BY_GENERATION-1)) = populationTree->searchElement(*populationSize - SUBJECTS_BY_GENERATION + i);
                //Busca la posicion real del nuevo miembro
                for(int j = 2*SUBJECTS_BY_GENERATION-1; j > 0; j--){
                    //Si la posicion anterior es mejor, hace el cambio
                    if((*(fittest + j))->getFitness() > (*(fittest + j-1))->getFitness()){
                        //Toma temporal y hace swap
                        Subject* tmp = *(fittest + j-1);
                        *(fittest + j-1) = *(fittest + j);
                        *(fittest + j) = tmp;
                    }
                }
            }
        }
    }else{
        //Busca la cantidad de padres necesaria con mejor fitness
        for(int i = 0; i < 2*SUBJECTS_BY_GENERATION; i++){
            *(fittest+i) = populationTree->searchElement(i+1);
        }
    }
}

/**@brief bandera de extincion
 * @return bool
 */
void Population::exterminate(){
    killEmAll();
    *defunct = true;
    (*activePopulationsOnManager)--;
}

/**Accede al pthread
 * return pthread_t*
 */
pthread_t* Population::get_pthread(){
    return reproduction_pthread;
}

/**@brief elimina el pthread
 */
void Population::delete_pthread(){
    free(reproduction_pthread);
}

/**@brief Metodo del pthread
 * @param void* populationParameter: poblacion
 */
void* reproductionThread(void* parameter){
    //Se obtiene la poblacion
    Population* population = static_cast<Population*>(static_cast<PThreadParam*>(parameter)->getExcecutioner());
    //Se crea el laboratorio
    LifeLaboratory* laboratory = static_cast<LifeLaboratory*>(malloc(sizeof(LifeLaboratory)));
    new(laboratory) LifeLaboratory(population);
    //Se crea controlador de tiempo
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=10;
    //Primera generacion
    laboratory->createPopulation();
    pthread_cond_signal(static_cast<PThreadParam*>(parameter)->getCondition());
    //Loop que se ejecutara mientras la poblacion viva
    while(!population->isDefunct()){
        nanosleep(&timeController, NULL);
        laboratory->createGeneration();
    }
    free(&timeController);
    population->delete_pthread();
    return 0;
}