//
// Created by pablo on 22/04/15.
//

#ifndef PROJECTMIDGARD_SUBJECT_H
#define PROJECTMIDGARD_SUBJECT_H

#define FATHERID "FATHERID  "
#define MOTHERID " / MOTHERID  "
#define SUBJECTID " / SUBJECTID "
#define POPULATIONID " / POPULATIONID "
#define FITNESS " / FITNESS  "
#define GENERATION " / GENERATION "
#define GEN " / GEN "
#define CHARACTERISTICS " / CHARACTERISTICS "

static const int OFFSET_ATTACK = 1;

#include "Chromosome.h"
#include "../Algorithms/GeneralFitnessCalculator.h"
#include "../Data/PThreadParam.h"
#include "Terrain.h"
#include "../Data/FileManager.h"
#include "iostream"
#include "string"
#include "../Network/SocketLogic.h"
#include "MovilObjectManager.h"

#define ID_STR "ID: "
#define GENERATION_STR "GENERATION: "
#define FITNESS_STR "FITNESS: "
#define FATHER_STR "FATHER: "
#define MOTHER_STR "MOTHER: "
#define NULL_PARENTS_STR "null, first generation"
#define LIFE_STATE_STR "LIFE STATE: "
#define PROFESSION_STR "PROFESSION: "
#define PROFESSION_WARRIOR_STR "Warrior"
#define PROFESSION_DEFENSE_STR "Defense"
#define PROFESSION_MAGICIAN_STR "Magician"
#define PROFESSION_ENGINEER_STR "Engineer"
#define PROFESSION_PREACHER_STR "Preacher"
#define PROFESSION_QUACK_STR "Quack"

/** Clase Subject
 * @brief clase a la cual pertenecen todos los individuos vivos
 * @caracteristicas: edad, experiencia, salud, ataque, velocidad, defensa,
 *                   inteligencia, magia, runes-energia, blot, supersticion,
 *                   arma, armadura
*/
class Subject {
    Subject* father; //padre del individuo
    Subject* mother; //padre del individuo
    Subject* opponent;
    Chromosome* geneticInformation;
    Vector2D* position;
    pthread_t* lifeThread;
    int* actualYear;
    int* generation;
    long* id;
    float* fitness;
    bool* selected;
    unsigned char* characteristics;//vida-experiencia-arma-armadura-profesion
    std::string writeFileVariable;
    void calculateFitness();//funcion de calcular fitness y set fitness
    void findPath(Vector2D);
    bool findObjectPath(Vector2D);
    void printGeneralData();
    void printProfession();
    void printParents();
public:
    Subject(long,int*,unsigned char*,Vector2D);
    Subject(long,int*,unsigned char*,Vector2D, int);
    Subject(Subject*,Subject*,Chromosome*,long,long,int*);
    Subject(const Subject&);
    ~Subject();
    static int actionSleepNano;
    long getGeneration();
    long getID();
    Chromosome* getGeneticInformation();
    Subject* getFather(); // Obtiene padre 1
    Subject* getMother(); // Obtiene padre 2
    float getFitness();
    unsigned char getCharacteristic(int);
    void setCharacteristic(char, int);
    void attack();
    void updateLife();
    bool isAlive();
    void kill();
    pthread_t* get_p_thread();
    void start_p_thread();
    void setOpponent(Subject*);
    void delete_p_thread();
    Subject* getOpponent();
    void optionSelection();
    void selectProfession();
    void print();
    void changeSelection(bool);
    bool isSelected();
    void create();
    void makeSubjectFile();
    void readSubjectFIle();
};

void* subjectLife(void*);

#endif //PROJECTMIDGARD_SUBJECT_H
