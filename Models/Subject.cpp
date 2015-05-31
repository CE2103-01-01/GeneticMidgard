//
// Created by pablo on 22/04/15.
//

#include "Subject.h"
#include "Terrain.h"
#include "../Network/SocketLogic.h"
#include "movilObjectManager.h"

using namespace pugi;
using namespace constantsSubjectXML;
int Subject::actionSleepNano = 20;
/** Constructor
 * @brief genera un individuo de primera generacion
 */
Subject::Subject(long idParam, int* actualYearParam, unsigned char* colors,Vector2D basePosition){
    //Ano actual
    actualYear = actualYearParam;
    selected = static_cast<bool*>(malloc(sizeof(bool)));
    *selected = false;
    //Crea y asigna id
    id = static_cast<long*>(malloc(sizeof(long)));
    *id = idParam;
    //Crea y asigna generacion
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = 0;
    //Crea y asigna la informacion genetica
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    *geneticInformation = Chromosome(colors, colors+1, colors+2);
    //Calcula fitness
    fitness = static_cast<float*>(malloc(sizeof(float)));
    calculateFitness();
    //Crea las caracteristicas
    characteristics = static_cast<unsigned char*>(calloc(0,NUMBER_OF_CHARACTERISTICS));
    //Vida maxima, convierte el rango del gen (de 0-255 a 0-100)
    *(characteristics + POSITION_OF_CHARACTERISTIC_LIFE) = 100;
    //Crea posicion
    position = static_cast<Vector2D*>(malloc(sizeof(Vector2D)));
    *position = basePosition;
    selectProfession();
    //Asigna padres
    father = NULL;
    mother = NULL;
    opponent = NULL;
    //Coloca en 0 el puntero al thread
    lifeThread = NULL;
}

/** Constructor
 * @brief genera un individuo de generacion N
 */
Subject::Subject(Subject* fatherParam, Subject* motherParam, Chromosome* geneticInformationParam,
                 long generationParam, long idParam, int* actualYearParam){
    //Ano actual
    actualYear = actualYearParam;
    selected = static_cast<bool*>(malloc(sizeof(bool)));
    *selected = false;
    id = static_cast<long*>(malloc(sizeof(long)));
    *id = idParam;
    //Crea y asigna generacion
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = generationParam;
    //Crea y asigna la informacion genetica
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    *geneticInformation = *geneticInformationParam;
    //Calcula fitness
    fitness = static_cast<float*>(malloc(sizeof(float)));
    calculateFitness();
    //Crea las caracteristicas
    characteristics = static_cast<unsigned char*>(calloc(0,NUMBER_OF_CHARACTERISTICS));
    //Vida maxima, convierte el rango del gen (de 0-255 a 0-100)
    *(characteristics + POSITION_OF_CHARACTERISTIC_LIFE) = 100;
    position = static_cast<Vector2D*>(malloc(sizeof(Vector2D)));
    *position = Terrain::getFreePositionNear(*fatherParam->position);
    //Asigna padres
    father = fatherParam;
    mother = motherParam;
    opponent = NULL;
    //Coloca en 0 el puntero al thread
    lifeThread = NULL;
    selectProfession();
}

/** Constructor
 * @brief genera un individuo de generacion N
 */
Subject::Subject(const Subject& other){
    //Ano actual
    actualYear = other.actualYear;
    selected = static_cast<bool*>(malloc(sizeof(bool)));
    *selected = *other.selected;
    //crea posicion
    position = static_cast<Vector2D*>(malloc(sizeof(Vector2D)));
    position->x = other.position->x;
    position->y = other.position->y;
    //Copia id
    id = static_cast<long*>(malloc(sizeof(long)));
    *id = *other.id;
    //Copia generacion
    generation = static_cast<int*>(malloc(sizeof(int)));
    *generation = *other.generation;
    //Copia fitness
    fitness = static_cast<float*>(malloc(sizeof(float)));
    *fitness = *other.fitness;
    //Copia informacion genetica
    geneticInformation = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    *geneticInformation = *other.geneticInformation;
    characteristics = static_cast<unsigned char*>(malloc(NUMBER_OF_CHARACTERISTICS));
    for(int i = 0; i<NUMBER_OF_CHARACTERISTICS; i++){
        *(characteristics + i) = *(other.characteristics + i);
    }
    father = other.father;
    mother = other.mother;
    opponent = other.opponent;
    lifeThread = other.lifeThread;
}

/** Destructor
 */
Subject::~Subject(){
    free(id);
    free(generation);
    free(characteristics);
    free(fitness);
    free(geneticInformation);
    free(position);
//    free(lifeThread);
    actualYear = NULL;
    father = NULL;
    mother = NULL;
 //   opponent = NULL;
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

/** @brief Modifica una caracteristica
 * @param unsigned char value:valor que modifica la caracteristica
 * @param int position:posicion donde es encuentra la caracteristica
 */
void Subject::setCharacteristic(unsigned char value, int position) {
    *(characteristics+position)+=value;
}

long Subject::getGeneration(){
    return *generation;
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
 * @return unsca a un sujetoigned char*
 */
unsigned char Subject::getCharacteristic(int position){
    return  *(characteristics + position);
}


/**@breif metodo que selecciona la profesion basado en el mejor gen
 */
void Subject::selectProfession() {
    switch(getGeneticInformation()->getBest()){
        case POSITION_OF_GENE_ATTACK:
            *(characteristics + POSITION_OF_CHARACTERISTIC_PROFESSION) = PROFESSION_WARRIOR;
            break;
        case POSITION_OF_GENE_DEFENSE:
            *(characteristics + POSITION_OF_CHARACTERISTIC_PROFESSION) = PROFESSION_DEFENSE;
            break;
        case POSITION_OF_GENE_MAGIC:
            *(characteristics + POSITION_OF_CHARACTERISTIC_PROFESSION) = PROFESSION_MAGICIAN;
            break;
        case POSITION_OF_GENE_INTELLIGENCE:
            *(characteristics + POSITION_OF_CHARACTERISTIC_PROFESSION) = PROFESSION_ENGINEER;
            break;
        case POSITION_OF_GENE_SUPERSTITION:
            *(characteristics + POSITION_OF_CHARACTERISTIC_PROFESSION) = PROFESSION_PREACHER;
            break;
        default:
            *(characteristics + POSITION_OF_CHARACTERISTIC_PROFESSION) = PROFESSION_QUACK;
            break;
    }
}

/**@breif metodo que selecciona la profesion basado en el mejor gen
 */
void Subject::printProfession() {
    switch(*(characteristics + POSITION_OF_CHARACTERISTIC_PROFESSION)){
        case PROFESSION_WARRIOR:
            std::cout << PROFESSION_STR << PROFESSION_WARRIOR_STR << std::endl;
            break;
        case PROFESSION_DEFENSE:
            std::cout << PROFESSION_STR << PROFESSION_DEFENSE_STR << std::endl;
            break;
        case PROFESSION_MAGICIAN:
            std::cout << PROFESSION_STR << PROFESSION_MAGICIAN_STR << std::endl;
            break;
        case PROFESSION_ENGINEER:
            std::cout << PROFESSION_STR << PROFESSION_ENGINEER_STR << std::endl;
            break;
        case PROFESSION_PREACHER:
            std::cout << PROFESSION_STR << PROFESSION_PREACHER_STR << std::endl;
            break;
        default:
            std::cout << PROFESSION_STR << PROFESSION_QUACK_STR << std::endl;
            break;
    }
}
/**@brief sigue un camino hasta una ruta definida
 * @param Vector2D positionToFind: posicion a encontrar en el mapa
 */
void Subject::findPath(Vector2D positionToFind) { /* (7 + 68N)T */
    //Se crea el controlador de tiempo
    struct timespec timeController;
    timeController.tv_nsec=0;
    timeController.tv_sec=1;
    Stack<Vector2D> path = Terrain::findPathAS(*position,*opponent->position);
    while (opponent->position->x-OFFSET_ATTACK > position->x || position->x > opponent->position->x+OFFSET_ATTACK
           || opponent->position->y-OFFSET_ATTACK > position->y || position->y > opponent->position->y+OFFSET_ATTACK) {

        if(!opponent || !opponent->isAlive()) break;
        if(positionToFind != *opponent->position) path = Terrain::findPathAS(*position,*opponent->position);
        if (path.size()==0) break;

        Vector2D next = path.top();                                                                         //5T
        position->x = next.x;                                                                               //5T
        position->y = next.y;
        updateSubject(*id, position->x, position->y);                                                       //6T
        path.pop();

        nanosleep(&timeController, NULL);
    }
}

bool Subject::findObjectPath(Vector2D positionToFind){
    Stack<Vector2D> path = Terrain::findPathAS(*position,positionToFind);
    if(path.size()==0) return false;
    while(path.size()!=0)
    {
        Vector2D next = path.top();                                                                         //5T
        position->x = next.x;                                                                               //5T
        position->y = next.y;                                                                               //5T
        sf::sleep(microseconds(actionSleepNano));                                                           //4T
        updateSubject(*id, position->x, position->y);                                                       //6T
        path.pop();
    }
    return true;
}

/**@brief imprime los datos de sujeto
 */
void Subject::printGeneralData(){
    std::cout << ID_STR << *id << std::endl;
    std::cout << GENERATION_STR << *generation << std::endl;
    std::cout << FITNESS_STR << *fitness << std::endl;
    std::cout << LIFE_STATE_STR << isAlive() << std::endl;
    printProfession();
}

/**@brief imprime los padres del sujeto
 */
void Subject::printParents(){
    if(father != 0){
        std::cout << FATHER_STR << father->getID() << std::endl;
        std::cout << MOTHER_STR << mother->getID() << std::endl;
    }else{
        std::cout << FATHER_STR << NULL_PARENTS_STR << std::endl;
        std::cout << MOTHER_STR << NULL_PARENTS_STR << std::endl;
    }
}

/**@brief imprime los datos de sujeto
 */
void Subject::print(){
    printGeneralData();
    printParents();
}


/** @brief Ataque
 */
void Subject::attack(){/* 70T */
    findPath(*opponent->position);                                                                                 //3T
    //Se suma el gen del ataque del atacante con la caracteristica arma
    int attackResult = geneticInformation->getGene(POSITION_OF_GENE_ATTACK)                                         //19T
                       + *(characteristics+POSITION_OF_CHARACTERISTIC_WEAPON)
                       + geneticInformation->getGene(POSITION_OF_GENE_DEFENSE)
                       + *(characteristics+POSITION_OF_CHARACTERISTIC_ARMOR);
    //Se suma el gen de la defensa del oponente con la caracteristica armadura
    int defenseResult = opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_ATTACK)                         //23T
                        + opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_DEFENSE)
                        + opponent->getCharacteristic(POSITION_OF_CHARACTERISTIC_WEAPON)
                        + opponent->getCharacteristic(POSITION_OF_CHARACTERISTIC_ARMOR);
    //Si el primer elemento de la comparacion es mayor, el ataque es mayor que la defensa, por lo tanto acierta
    if(attackResult >= defenseResult){                                                                              //3T
        if(trueRandom::getRandom()%256 < geneticInformation->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_BLOT)){   //18T
            opponent->kill();                                                                                     //2T
        }else if(trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < geneticInformation->getGene(POSITION_OF_GENE_BLOT)){                  //18T
            kill();
        }else if(attackResult > defenseResult){                                                                     //3T
            opponent->setCharacteristic(defenseResult-attackResult,POSITION_OF_CHARACTERISTIC_LIFE);                //6T
            lifeUpdate(opponent->getID(),defenseResult-attackResult);                                               //6T
        }else{
            opponent->setCharacteristic(ATTACK_DAMAGE,POSITION_OF_CHARACTERISTIC_LIFE);                             //4T
            lifeUpdate(opponent->getID(),ATTACK_DAMAGE);                                                            //4T
            this->setCharacteristic(ATTACK_DAMAGE,POSITION_OF_CHARACTERISTIC_LIFE);                                 //4T
            lifeUpdate(*id,ATTACK_DAMAGE);                                                                          //3T
        }
    }//Si el primer elemento de la comparacion es menor, el ataque es menor que la defensa, por lo tanto no acierta
    else{
        if(trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < geneticInformation->getGene(POSITION_OF_GENE_BLOT)){                  //18T
            kill();
        }else if(trueRandom::getRandom()%256 < geneticInformation->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_BLOT)){   //18T
            opponent->kill();
        }else{
            *(characteristics+POSITION_OF_CHARACTERISTIC_LIFE) += (attackResult - defenseResult);                   //9T
            lifeUpdate(*id,attackResult - defenseResult);                                                           //5T
        }
    }
}

/** @brief Retorna true si el jugador esta vivo, para ello la vida debe ser mayor a 0 y menor o igual a la edad
 * @return bool
 */
bool Subject::isAlive(){
    return *(characteristics + POSITION_OF_CHARACTERISTIC_AGE) <= *(characteristics + POSITION_OF_CHARACTERISTIC_LIFE) > 0;
}

/** @brief Mata al jugador colocando en false la bander
 */
void Subject::kill(){
    *(characteristics + POSITION_OF_CHARACTERISTIC_LIFE) = 0;
}

/**@brief Agrega un oponente
 * @param Subject* opponentParam: oponente a setear
 */
void Subject::setOppenent(Subject* opponentParam){
    opponent = opponentParam;
}

/**@brief Metodo que inicia el pthread
 */
Subject* Subject::getOpponent(){
    return opponent;
}

/** @brief cambia bandera de seleccionado
 */
void Subject::changeSelection(bool selecteParam){
    *selected = selecteParam;
}

/** @brief Accede a bandera de seleccionado
 * @return bool
 */
bool Subject::isSelected(){
    return *selected;
}

/** @brief Mata al jugador colocando en false la bander
 */
void Subject::updateLife(){
    *(characteristics + POSITION_OF_CHARACTERISTIC_AGE) = *actualYear - *generation;
}

/**@brief: accede al pthread
 * @return pthread_t*
 */
pthread_t* Subject::get_p_thread(){
    return lifeThread;

}

/**@brief envia create al socket
 */
void Subject::create(){
    createSubject(*id,position->x,position->y,geneticInformation->getGene(POSITION_OF_GENE_RED),
                  geneticInformation->getGene(POSITION_OF_GENE_GREEN),geneticInformation->getGene(POSITION_OF_GENE_BLUE));
}

/**@brief Metodo que inicia el pthread
 */
void Subject::start_p_thread(){
    Vector2D positionsVector = Terrain::getRandomFreePosition();
    Terrain::set(positionsVector,*id);
    //parametros
    create();
    void* parameters = malloc(sizeof(PThreadParam));
    new(static_cast<PThreadParam*>(parameters)) PThreadParam(this,NULL,NULL);
    //thread
    lifeThread = static_cast<pthread_t*>(malloc(sizeof(pthread_t)));
    pthread_create(lifeThread,NULL,subjectLife,parameters);
}

/**@brief Metodo que inicia el pthread
 */
void Subject::delete_p_thread(){
    free(lifeThread);
}

void Subject::optionSelection() {
    movilObject* object = movilObjectManager::getInstance()->getRandomObject();
    ;
    if(findObjectPath(object->getVector()))
        object->applyEffect(this);
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
    timeController.tv_nsec=0;
    timeController.tv_sec=1;
    //Este while corre hasta que se llame al metodo kill()
    while(excecutioner->isAlive()){
        //Espera un segundo
        nanosleep(&timeController, NULL);
        //Llama al metodo de vida del sujeto
        excecutioner->updateLife();
        //Si existe oponente ataca
        if(excecutioner->getOpponent()!=NULL && excecutioner->getOpponent()->isAlive()){
            excecutioner->attack();
            excecutioner->setOppenent(NULL);
        }//Si no existe oponente selecciona random un objeto
        else{
            excecutioner->optionSelection();
        }
    }
    deleteSubject(excecutioner->getID());
    return 0;
}

/**
 *FatherID | MotherID | SubjectID | SubjectGeneration | SubjectGens |SubjectCharacteristics
 * 8bytes  |  8bytes  |   8bytes  |       4bytes      |    13bytes  |       8bytes
 */
void Subject::makeSubjectFile()
{
    writeFileVariable = "";

    if(father != 0 && mother != 0)
    {
        writeFileVariable.append(FATHERID);
        writeFileVariable.append(std::to_string(father->getID()/SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID));
        writeFileVariable.append(MOTHERID);
        writeFileVariable.append(std::to_string(mother->getID()/SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID));
    }

    writeFileVariable.append(SUBJECTID);
    writeFileVariable.append(std::to_string(*(id)/SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID));
    writeFileVariable.append(POPULATIONID);
    writeFileVariable.append(std::to_string(*(id)%SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID));
    writeFileVariable.append(FITNESS);
    writeFileVariable.append(std::to_string(getFitness()));
    writeFileVariable.append(GENERATION);
    writeFileVariable.append(std::to_string(*generation));

    for(int i = 0; i < NUMBER_OF_GENES; i++)
    {
        writeFileVariable.append(GEN);
        writeFileVariable.append(std::to_string(i) + ":");
        writeFileVariable.append(" ");
        writeFileVariable.append(std::to_string(geneticInformation->getGene(i)));
    }

    for(int j = 0; j < NUMBER_OF_CHARACTERISTICS; j++)
    {
        writeFileVariable.append(CHARACTERISTICS);
        writeFileVariable.append(std::to_string(j)) + ":";
        writeFileVariable.append(" ");
        writeFileVariable.append(std::to_string(*(characteristics + j)));
    }
    FileManager::writeFile(writeFileVariable.c_str(), *(id)/SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID, writeFileVariable.length());
}

/**
 *
 */
void Subject::readSubjectFIle()
{
    char* reader_variable = static_cast<char*>(malloc(writeFileVariable.length()));

    FileManager::readFile(reader_variable, *(id)/SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID, writeFileVariable.length());

    std::cout << reader_variable << std::endl;

}
