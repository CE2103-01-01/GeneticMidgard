//
// Created by pablo on 22/04/15.
//

#include "Subject.h"

using namespace pugi;
using namespace constantsSubjectXML;

/** Constructor
 * @brief genera un individuo de primera generacion
 */
Subject::Subject() {
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(geneticInformation) Chromosome();
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = 0;
    fitness = static_cast<int*>(malloc(sizeof(int)));
    calculateFitness();
    profession = "";
    race ="";
    weapon = 0; //TODO:  revisar si se debe cambiar
    armor = 0; //TODO:  revisar si se debe cambiar
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
                 Chromosome* geneticInformationParam, int generationParam){

    geneticInformation = geneticInformationParam;
    fitness = static_cast<int*>(malloc(sizeof(int)));
    calculateFitness();
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = generationParam;
    profession = "";
    race=""
    weapon = 0;
    armor = 0;
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
/** @brief Modifica la salud
 * @param int number:valor que modifica salud
 */
void Subject::setHealth(int number) {
    *(characteristics+POSITION_OF_HEALTH)=*(characteristics+POSITION_OF_HEALTH)+(unsigned char)number;
}
/** @brief Modifica el ataque
 * @param int number:valor que modifica ataque
 */
void Subject::setAttack(int number) {
    *(characteristics+POSITION_OF_ATTACK)=*(characteristics+POSITION_OF_ATTACK)+(unsigned char)number;
}
/** @brief Modifica la defensa
 * @param int number:valor que modifica defensa
 */
void Subject::setDefense(int number) {
    *(characteristics+POSITION_OF_DEFENSE)=*(characteristics+POSITION_OF_DEFENSE)+(unsigned char)number;
}
/** @brief Modifica la energia
 * @param int number:valor que modifica energia
 */
void Subject::setEnergy(int number) {
    *(characteristics+POSITION_OF_ENERGY)=*(characteristics+POSITION_OF_ENERGY)+(unsigned char)number;
}
/** @brief Modifica la blot
 * @param int number:valor que modifica blot
 */
void Subject::setBlot(int number) {
    *(characteristics+POSITION_OF_BLOT)=*(characteristics+POSITION_OF_BLOT)+(unsigned char)number;
}
/** @brief Modifica la inteligencia
 * @param int number:valor que modifica inteligencia
 */
void Subject::setIntelligent(int number) {
    *(characteristics+POSITION_OF_INTELLIGENCE)=*(characteristics+POSITION_OF_INTELLIGENCE)+(unsigned char)number;
}
/** @brief Modifica la magia
 * @param int number:valor que modifica magia
 */
void Subject::setMagic(int number) {
    *(characteristics+POSITION_OF_MAGIC)=*(characteristics+POSITION_OF_MAGIC)+(unsigned char)number;
}

/** @brief Accede a la generacion
 * @return int
 */
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
 * @return int
 */
int Subject::getFitness(){
    return *fitness;
};

/** @brief calcular  fitness
 *
 */
void Subject::calculateFitness() {
    xml_document constantXml;
    constantXml.load_file(CONSTANT_XML_PATH);
    int* index = static_cast<int*>(malloc(sizeof(int)));
    (*index)=0;
    for(xml_attribute attrIter = constantXml.child(CONSTANT_XML_ROOT).child(profession).first_attribute();
        attrIter && (*index)<NUMBER_OF_CHARACTERISTICS; attrIter = attrIter.next_attribute(), (*index)++) {
            (*fitness) += attrIter.as_int() * (*(characteristics + (*index)));
    }
    free(index);
};

/** @brief Accede al armadura
 * @return Armor*
 */
Armor* Subject::getArmor(){
    return armor;
};

/** @brief Accede al arma
 * @return Weapon*
 */
Weapon* Subject::getWeapon(){
    return weapon;
};