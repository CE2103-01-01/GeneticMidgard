//
// Created by pablo on 22/04/15.
//

#include "Subject.h"
#include "../Algorithms/ChromosomeMixer.h"

using namespace pugi;
using namespace constantsSubjectXML;

/** Constructor
 * @brief genera un individuo de primera generacion
 */
Subject::Subject(int idParam){
    id = idParam;
    alive = true;
    geneticInformation = Chromosome();
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = 0;
    fitness = static_cast<float*>(malloc(sizeof(float)));
    calculateFitness();
    profession = "";
    race ="";
    characteristics = static_cast<unsigned char*>(malloc(NUMBER_OF_CHARACTERISTICS));
    for(int i = 0; i < NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i) = 0;    //TODO: MODIFICAR
    }
    father = 0;
    mother = 0;
}

/** Constructor
 * @brief genera un individuo de generacion N
 */
Subject::Subject(Subject* fatherParam, Subject* motherParam, Chromosome geneticInformationParam,
                 int generationParam, int idParam){
    id = idParam;
    alive = true;
    geneticInformation = geneticInformationParam;
    fitness = static_cast<float*>(malloc(sizeof(float)));
    calculateFitness();
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = generationParam;
    profession = "";
    race="";
    characteristics = static_cast<unsigned char*>(malloc(NUMBER_OF_CHARACTERISTICS));
    for(int i = 0; i<NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i) = 0;    //TODO: MODIFICAR
    }
    father = fatherParam;
    mother = motherParam;
}

Subject::~Subject(){
    alive = false;
    free(generation);
    free(characteristics);
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
    return geneticInformation;
}

/** @brief Accede a la salud
 * @return unsigned char
 */
unsigned char Subject::getHealth(){
    return *(characteristics + POSITION_OF_HEALTH);
}
/** @brief Modifica una caracteristica
 * @param int value:valor que modifica la caracteristica
 * @param char position:posicion donde es encuentra la caracteristica
 */
void Subject::setCharacteristic(int value, char position) {
    *(characteristics+position)=*(characteristics+position)+(unsigned char)value;
};
int Subject::getGeneration(){
    return *generation;
}

/** @brief Accede a la edad
 * @return unsigned char
 */
unsigned char Subject::getAge(){
    return *(characteristics + POSITION_OF_AGE);
}

/** @brief Accede a la experiencia
 * @return unsigned char
 */
unsigned char Subject::getExperience(){
    return  *(characteristics + POSITION_OF_EXPERIENCE);
}

/** @brief Accede al fitness
 * @return float
 */
float Subject::getFitness(){
    return *fitness;
}

/** @brief Accede al ID
 * @return float
 */
int Subject::getID(){
    return id;
}

/** @brief calcular  fitness
 *
 */
void Subject::calculateFitness() {
    GeneralFitnessCalculator* calculator = ChromosomeMixer::getInstance()->getCalculator();
    (*fitness) = calculator->calculateFitness(geneticInformation);
}

/** @brief Accede al armadura
 * @return unsigned char*
 */
unsigned char Subject::getArmor(){
    return  *(characteristics + POSITION_OF_ARMOR);
}

/** @brief Accede al arma
 * @return unsigned char*
 */
unsigned char Subject::getWeapon(){
    return *(characteristics + POSITION_OF_WEAPON);
}

/** @brief Retorna true si el jugador esta vivo
 * @return bool
 */
bool Subject::isAlive(){
    return alive;
}

/** @brief Mata al jugador colocando en false la bander
 */
void Subject::kill(){
    (alive) = 0;
}

/** @brief Mata al jugador colocando en false la bander
 */
void Subject::life(){
    std::cout << "Hello, my ID is: "<< (id) <<std::endl;
}

/**@brief: accede al pthread
 * @return pthread_t*
 */
pthread_t* Subject::get_p_thread(){
    return &lifeThread;
}

/**@brief Metodo que inicia el pthread
 * @param Subject* subject: sujeto sobre el que se ejecuta
 */
void Subject::start_p_thread(){
    void* parameters = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(parameters)) PThreadParam(this,0);
    pthread_create(&lifeThread,0,subjectLife,parameters);
}

/**@brief metodo ejecutado por el pthread
 * @param void* parameter: es el PThreadParam que contiene los datos necesarios para la ejecucion
 * @return 0
 */
void* subjectLife(void* parameter){
    //Castea el parametro y extrae el sujeto
    Subject* excecutioner = static_cast<Subject*>(static_cast<PThreadParam*>(parameter)->getExcecutioner());
    //Crea estructura para tiempo
    struct timespec timeControler;
    timeControler.tv_nsec=0;
    timeControler.tv_sec=1;
    int life = 100;
    //Este while corre hasta que se llame al metodo kill()
    while(life > 0){
        //Llama al metodo de vida del sujeto
        //excecutioner->life();
        //Espera un segundo
        nanosleep(&timeControler, 0);
        life--;
    }
    std::cout << "Goodbye, I was: " << excecutioner->getID() <<std::endl;
    return 0;
}