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
    weapon = 0; //TODO:  revisar si se debe cambiar
    armor = 0; //TODO:  revisar si se debe cambiar
    characteristics = static_cast<int*>(malloc(NUMBER_OF_CHARACTERISTICS * sizeof(int)));
    for(int i = 0; i < NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i*sizeof(int)) = 0;    //TODO: MODIFICAR
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
    weapon = 0;
    armor = 0;
    characteristics = static_cast<int*>(malloc(NUMBER_OF_CHARACTERISTICS * sizeof(int)));
    for(int i = 0; i<NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i*sizeof(int)) = 0;    //TODO: MODIFICAR
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
 * @return int
 */
int Subject::getHealth(){
    return *(characteristics + POSITION_OF_HEALTH*sizeof(int));
}

/** @brief Accede a la generacion
 * @return int
 */
int Subject::getGeneration(){
    return *generation;
}

/** @brief Accede a la edad
 * @return int
 */
int Subject::getAge(){
    return *(characteristics + POSITION_OF_AGE*sizeof(int));
}

/** @brief Accede a la experiencia
 * @return int
 */
int Subject::getExperience(){
    return  *(characteristics + POSITION_OF_EXPERIENCE*sizeof(int));
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
    int* constants = static_cast<int*>(malloc(NUMBER_OF_CHARACTERISTICS * sizeof(int)));
    initConstants(constants);
    for(int i = 0; i<NUMBER_OF_CHARACTERISTICS;i++){
        (*fitness) += (*(constants + i*sizeof(int))) * (*(characteristics + i*sizeof(int)));
    }
}

void Subject::initConstants(int* constants){
    xml_document constantXml;
    constantXml.load_file(CONSTANT_XML_PATH);
    int index = 0;
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(AGE_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(EXPERIENCE_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(HEALTH_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(ATTACK_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(SPEED_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(DEFENSE_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(INTELLIGENCE_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(MAGIC_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(RUNES_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(BLOT_XML).as_int());
    *(constants + (++index)*sizeof(int)) =
            (constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute(SUPERSTITION_XML).as_int());
}
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

