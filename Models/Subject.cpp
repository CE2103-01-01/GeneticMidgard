//
// Created by pablo on 22/04/15.
//

#include "Subject.h"

/** Constructor
 * @brief genera un individuo de primera generacion
 */
Subject::Subject() {
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(geneticInformation) Chromosome();
    health = static_cast<int*>(malloc(sizeof(int)));
    *health = 0;    //TODO: cambiar
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = 0;
    age = static_cast<int*>(malloc(sizeof(int)));
    *age = 0;
    experience = static_cast<int*>(malloc(sizeof(int)));
    *experience = 0;
    fitness = static_cast<int*>(malloc(sizeof(int)));
    *fitness = 0; //TODO: cambiar
    father = 0;
    mother = 0;
    weapon = 0; //TODO:  revisar si se debe cambiar
    armor = 0; //TODO:  revisar si se debe cambiar
}

/** Constructor
 * @brief genera un individuo de generacion N
 */
Subject::Subject(Subject* fatherParam, Subject* motherParam) {
    geneticInformation = 0; //TODO: cambiar
    health = static_cast<int*>(malloc(sizeof(int)));
    *health = 0;    //TODO: cambiar
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = 0; //TODO: cambiar
    age = static_cast<int*>(malloc(sizeof(int)));
    *age = 0;
    experience = static_cast<int*>(malloc(sizeof(int)));
    *experience = 0;
    fitness = static_cast<int*>(malloc(sizeof(int)));
    *fitness = 0; //TODO: cambiar
    father = fatherParam;
    mother = motherParam;
    weapon = 0; //TODO:  revisar si se debe cambiar
    armor = 0; //TODO:  revisar si se debe cambiar
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
    return *health;
};

/** @brief Accede a la generacion
 * @return int
 */
int Subject::getGeneration(){
    return *generation;
};

/** @brief Accede a la edad
 * @return int
 */
int Subject::getAge(){
    return *age;
};

/** @brief Accede a la experiencia
 * @return int
 */
int Subject::getExperience(){
    return *experience;
};

/** @brief Accede al fitness
 * @return int
 */
int Subject::getFitness(){
    return *fitness;
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