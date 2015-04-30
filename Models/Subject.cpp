//
// Created by pablo on 22/04/15.
//

#include "Subject.h"


using namespace pugi;

/** Constructor
 * @brief genera un individuo de primera generacion
 */
Subject::Subject() {
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(geneticInformation) Chromosome();
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = 0;
    fitness = static_cast<int*>(malloc(sizeof(int)));
    *fitness = 0; //TODO: cambiar
    father = 0;
    profession = "";
    mother = 0;
    weapon = 0; //TODO:  revisar si se debe cambiar
    armor = 0; //TODO:  revisar si se debe cambiar
    for(int i = 0; i<12;i++){
        caracteristics.append(0);
    }
}

/** Constructor
 * @brief genera un individuo de generacion N
 */
Subject::Subject(Subject* fatherParam, Subject* motherParam) {
    geneticInformation = 0; //TODO: cambiar
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = 0; //TODO: cambiar
    fitness = static_cast<int*>(malloc(sizeof(int)));
    *fitness = 0; //TODO: cambiar
    father = fatherParam;
    mother = motherParam;
    weapon = 0; //TODO:  revisar si se debe cambiar
    armor = 0; //TODO:  revisar si se debe cambiar
    for(int i = 0; i<12;i++){
        caracteristics.append(0);
    }
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
    return *caracteristics.getNode(2)->getData();
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
    return *caracteristics.getNode(0)->getData();
}

/** @brief Accede a la experiencia
 * @return int
 */
int Subject::getExperience(){
    return  *caracteristics.getNode(1)->getData();
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
    DoubleList<int> constants;
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("age").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("experience").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("health").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("attack").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("speed").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("defense").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("intelligence").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("magic").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("runes").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("blot").as_int());
    constants.append(constantXml.child(CONSTANT_XML_ROOT).child(profession.c_str()).attribute("superstition").as_int());
    for(int i = 0; i<12;i++){
        *fitness+=(*constants.getNode(i)->getData())*(*caracteristics.getNode(i)->getData());
    }
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

