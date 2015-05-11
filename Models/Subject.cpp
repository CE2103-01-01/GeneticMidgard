//
// Created by pablo on 22/04/15.
//

#include "Subject.h"
#include "Terrain.h"
#include "../Network/SocketLogic.h"

using namespace pugi;
using namespace constantsSubjectXML;

/** Constructor
 * @brief genera un individuo de primera generacion
 */
Subject::Subject(long idParam){
    id = static_cast<long*>(malloc(sizeof(long)));
    generation = static_cast<long*>(malloc(sizeof(long)));
    alive = static_cast<bool*>(malloc(sizeof(bool)));
    profession = static_cast<char*>(malloc(sizeof(char)));
    fitness = static_cast<float*>(malloc(sizeof(float)));
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    characteristics = static_cast<unsigned char*>(malloc(NUMBER_OF_CHARACTERISTICS));
    *id = idParam;
    *alive = true;
    *geneticInformation = Chromosome();
    *generation = 0;
    *profession = 0;
    for(int i = 0; i < NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i) = 0;    //TODO: MODIFICAR
    }
    calculateFitness();
    father = 0;
    mother = 0;
    lifeThread = 0;
    position = 0;
}

/** Constructor
 * @brief genera un individuo de generacion N
 */
Subject::Subject(Subject* fatherParam, Subject* motherParam, Chromosome* geneticInformationParam,
                 long generationParam, long idParam){
    id = static_cast<long*>(malloc(sizeof(long)));
    generation = static_cast<long*>(malloc(sizeof(long)));
    alive = static_cast<bool*>(malloc(sizeof(bool)));
    profession = static_cast<char*>(malloc(sizeof(char)));
    fitness = static_cast<float*>(malloc(sizeof(float)));
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    characteristics = static_cast<unsigned char*>(malloc(NUMBER_OF_CHARACTERISTICS));
    *id = idParam;
    *alive = true;
    *geneticInformation = *geneticInformationParam;
    *generation = generationParam;
    *profession = 0;
    for(int i = 0; i<NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i) = 0;    //TODO: MODIFICAR
    }
    father = fatherParam;
    mother = motherParam;
    calculateFitness();
    lifeThread = 0;
    position = 0;
}

/** Constructor
 * @brief genera un individuo de generacion N
 */
Subject::Subject(const Subject& other){
    if(other.position != 0){
    //    position = static_cast<int*>(malloc(2 * sizeof(int)));
    //    *(position) = *(other.position);
    //    *(position + 1) = *(other.position + 1);
    }
    id = static_cast<long*>(malloc(sizeof(long)));
    generation = static_cast<long*>(malloc(sizeof(long)));
    alive = static_cast<bool*>(malloc(sizeof(bool)));
    profession = static_cast<char*>(malloc(sizeof(char)));
    fitness = static_cast<float*>(malloc(sizeof(float)));
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    characteristics = static_cast<unsigned char*>(malloc(NUMBER_OF_CHARACTERISTICS));
    *id = *other.id;
    *alive = true;
    *geneticInformation = *other.geneticInformation;
    *generation = *other.generation;
    *profession = *other.profession;
    for(int i = 0; i<NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i) = *(other.characteristics + i);    //TODO: MODIFICAR
    }
    father = other.father;
    mother = other.mother;
    *fitness = *other.fitness;
    lifeThread = 0;
}

/** Destructor
 */
Subject::~Subject(){

}

/** @brief Accede al padre
 * @return Subject*
 */
Subject* Subject::getFather() {
    return father;
}

/** @brief Accede a la madre
 * @return Subject*
 */
Subject* Subject::getMother() {
    return mother;
}

/** @brief Accede al cromosoma
 * @return Chromosome*
 */
Chromosome Subject::getGeneticInformation() {
    return *geneticInformation;
}

/** @brief Modifica una caracteristica
 * @param int value:valor que modifica la caracteristica
 * @param char position:posicion donde es encuentra la caracteristica
 */
void Subject::setCharacteristic(unsigned char value, unsigned char position) {
    *(characteristics+position)=*(characteristics+position)+value;
}

long Subject::getGeneration(){
    return *generation;
}

/** @brief Accede al fitness
 * @return float
 */
float Subject::getFitness(){
    return 0;
}

/** @brief Accede al ID
 * @return float
 */
long Subject::getID(){
    return *id;
}

/** @brief calcular  fitness
 *
 */
void Subject::calculateFitness() {
    *fitness = GeneralFitnessCalculator::getInstance()->calculateFitness(geneticInformation);
}

/** @brief Accede a una caracteristica
 * @return unsigned char*
 */
unsigned char Subject::getCharacteristic(int position){
    return  *(characteristics + position);
}

/** @brief Retorna true si el jugador esta vivo
 * @return bool
 */
bool Subject::isAlive(){
    return *alive;
}

/** @brief Mata al jugador colocando en false la bander
 */
void Subject::kill(){
    *alive = false;
}

/** @brief Mata al jugador colocando en false la bander
 */
void Subject::life(){
    std::cout << "Hello, my ID is: "<< *id << " i am on " << *(position) << " , " << *(position+1) << std::endl;
}

/**@brief: accede al pthread
/**@brief Metodo que inicia el pthread
 * @return pthread_t*
 */
pthread_t* Subject::get_p_thread(){
    return lifeThread;

}
/**
 * @param Subject* subject: sujeto sobre el que se ejecuta
 */
void Subject::start_p_thread(){
    Vector2D positionsVector = Terrain::getRandomFreePosition();
    Terrain::set(positionsVector,*id);
    position = static_cast<int*>(malloc(2 * sizeof(int)));
    *(position) = positionsVector.x;
    *(position + 1) = positionsVector.y;
    void createSubject(unsigned int idSubject, unsigned int x, unsigned int y,
                       unsigned int r, unsigned int g, unsigned int b);
    void* parameters = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(parameters)) PThreadParam(this,NULL);
    lifeThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    pthread_create(lifeThread,NULL,subjectLife,parameters);
}

/**@brief metodo ejecutado por el pthread
 * @param void* parameter: es el PThreadParam que contiene los datos necesarios para la ejecucion
 * @return 0
 */
void* subjectLife(void* parameter){
    //Castea el parametro y extrae el sujeto
    Subject* excecutioner = static_cast<Subject*>(static_cast<PThreadParam*>(parameter)->getExcecutioner());
    //Crea estructura para tiempo
    struct timespec timeController;
    timeController.tv_nsec=500000000;
    timeController.tv_sec=1;
    int life = 5;
    //Este while corre hasta que se llame al metodo kill()
    while(excecutioner->isAlive()){
        //Llama al metodo de vida del sujeto
        excecutioner->life();
        //Espera un segundo
        nanosleep(&timeController, 0);
        life--;
        if(life==0){
            excecutioner->kill();
        }
    }
    std::cout << "Goodbye, I was: " << excecutioner->getID() <<std::endl;
    return 0;
}