//
// Created by pablo on 22/04/15.
//

#include "Subject.h"

using namespace pugi;
using namespace constantsSubjectXML;

/** Constructor
 * @brief genera un individuo de primera generacion
 */
Subject::Subject(int idParam) {
    id = static_cast<int*>(malloc(sizeof(int)));
    *id = idParam;
    alive = static_cast<bool*>(malloc(sizeof(bool)));
    *alive = true;
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(geneticInformation) Chromosome();
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
Subject::Subject(Subject* fatherParam, Subject* motherParam,
                 Chromosome* geneticInformationParam, int generationParam, int idParam){

    id = static_cast<int*>(malloc(sizeof(int)));
    *id = idParam;
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
Chromosome* Subject::getGeneticInformation() {
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
};

/** @brief calcular  fitness
 *
 */
void Subject::calculateFitness() {
    GeneralFitnessCalculator::init();
    (*fitness) = GeneralFitnessCalculator::calculateFitness(geneticInformation);
};

/** @brief Accede al armadura
 * @return unsigned char*
 */
unsigned char Subject::getArmor(){
    return  *(characteristics + POSITION_OF_ARMOR);
};

/** @brief Accede al arma
 * @return unsigned char*
 */
unsigned char Subject::getWeapon(){
    return *(characteristics + POSITION_OF_WEAPON);
};

/** @brief Retorna true si el jugador esta vivo
 * @return bool
 */
bool Subject::isAlive(){
    return (*alive);
};

/** @brief Mata al jugador colocando en false la bander
 */
void Subject::kill(){
    (*alive) = false;
    //TODO: mejorar cuando se implemente pthread
};
