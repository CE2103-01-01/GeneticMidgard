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
    //Asigna padres
    father = 0;
    mother = 0;
    opponent = 0;
    //Coloca en 0 el puntero al thread
    lifeThread = 0;
    makeSubjectFile();
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
    opponent = 0;
    //Coloca en 0 el puntero al thread
    lifeThread = 0;
    makeSubjectFile();
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
    makeSubjectFile();
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
    actualYear = 0;
    father = 0;
    mother = 0;
    opponent = 0;
    //FileManager::deleteFile(*(id));
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

void Subject::findPath(Vector2D* positionToFind) {
    while (!(position->x <= opponent->position->x- OFFSET_ATTACK && position->x >= opponent->position->x+ OFFSET_ATTACK
             && position->y <= opponent->position->y- OFFSET_ATTACK && position->y>= opponent->position->y+ OFFSET_ATTACK)) {
        Stack<Vector2D> path = Terrain::findPathAS(*position,*opponent->position);
        if (path.size()!=0) {
            Vector2D next = path.top();
            position->x = next.x;
            position->y = next.y;
            sf::sleep(microseconds(actionSleepNano));
            updateSubject(*id, position->x, position->y);
            //std::cout << "SE MOVIO" << std::endl;
            path.pop();
            if(*positionToFind== *opponent->position)
            {
                path = Terrain::findPathAS(*position,*opponent->position);
                *positionToFind = *opponent->position;

            }
        }
    }
}

/** @brief Ata
 */
void Subject::attack(){
    findPath(opponent->position);
    //Se suma el gen del ataque del atacante con la caracteristica arma
    int attackResult = geneticInformation->getGene(POSITION_OF_GENE_ATTACK)
                       + getCharacteristic(POSITION_OF_CHARACTERISTIC_WEAPON)
                       + getGeneticInformation()->getGene(POSITION_OF_GENE_DEFENSE)
                       + getCharacteristic(POSITION_OF_CHARACTERISTIC_ARMOR);
    //Se suma el gen de la defensa del oponente con la caracteristica armadura
    int defenseResult = opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_ATTACK)
                        + opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_DEFENSE)
                        + opponent->getCharacteristic(POSITION_OF_CHARACTERISTIC_WEAPON)
                        + opponent->getCharacteristic(POSITION_OF_CHARACTERISTIC_ARMOR);
    //Si el primer elemento de la comparacion es mayor, el ataque es mayor que la defensa, por lo tanto acierta
    if(attackResult >= defenseResult){
        if(trueRandom::getRandom()%256 < geneticInformation->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_BLOT)){
            opponent->kill();
        }else if(trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < geneticInformation->getGene(POSITION_OF_GENE_BLOT)){
            kill();
        }else if(attackResult > defenseResult){
            opponent->setCharacteristic(defenseResult-attackResult,POSITION_OF_CHARACTERISTIC_LIFE);
            lifeUpdate(opponent->getID(),defenseResult-attackResult);
        }else{
            opponent->setCharacteristic(ATTACK_DAMAGE,POSITION_OF_CHARACTERISTIC_LIFE);
            lifeUpdate(opponent->getID(),ATTACK_DAMAGE);
            this->setCharacteristic(ATTACK_DAMAGE,POSITION_OF_CHARACTERISTIC_LIFE);
            lifeUpdate(*id,ATTACK_DAMAGE);
        }
    }//Si el primer elemento de la comparacion es menor, el ataque es menor que la defensa, por lo tanto no acierta
    else{
        if(trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < opponent->getGeneticInformation()->getGene(POSITION_OF_GENE_BLOT)){
            opponent->kill();
        }else if(trueRandom::getRandom()%256 < getGeneticInformation()->getGene(POSITION_OF_GENE_RUNES) ||
                trueRandom::getRandom()%256 < getGeneticInformation()->getGene(POSITION_OF_GENE_BLOT)){
            kill();
        }else{
            this->setCharacteristic(attackResult - defenseResult,POSITION_OF_CHARACTERISTIC_LIFE);
            lifeUpdate(*id,attackResult - defenseResult);
        }
    }
    //std::cout << *id  << " vs " << opponent->getID() << " = " << (int)*(characteristics+POSITION_OF_CHARACTERISTIC_LIFE) << "-" << (int)opponent->getCharacteristic(POSITION_OF_CHARACTERISTIC_LIFE) << std::endl;
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
    deleteSubject(*id);
}

void Subject::optionSelection() {
    int value = trueRandom::randRange(0,100);
    movilObject objectToGet = movilObjectManager::getInstance()->getRandomObject();
    findPath(objectToGet.getVector());
    objectToGet.applyEffect(this);
}

/**@brief metodo ejecutado por el pthread
 * @param void* parameter: es el PThreadParam que contiene los datos necesarios para la ejecucion
 * @return 0
 */
void* subjectLife(void* parameter){
    //Castea el parametro y extrae el sujeto
    Subject* excecutioner = static_cast<Subject*>(static_cast<PThreadParam*>(parameter)->getExcecutioner());
    //std::cout << "Hello, I am: " << excecutioner->getID() <<std::endl;
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
           // excecutioner->optionSelection();
        }
    }
    //std::cout << "Goodbye, I was: " << excecutioner->getID() <<std::endl;
    excecutioner->delete_p_thread();
    return 0;
}

/**
 *FatherID | MotherID | SubjectID | SubjectGeneration | SubjectGens |SubjectCharacteristics
 * 8bytes  |  8bytes  |   8bytes  |       4bytes      |    13bytes  |       8bytes
 */
void Subject::makeSubjectFile()
{
    if(father != 0 && mother != 0)
    {
        FileManager::writeFile((std::to_string(mother->getID())).c_str(), *(id),
                               (std::to_string(father->getID())).length());

        FileManager::writeFile((std::to_string(mother->getID())).c_str(), *(id),
                               (std::to_string(mother->getID())).length());
    }


    FileManager::writeFile(std::to_string(*(id)).c_str(), *(id),
                           (std::to_string(*(id)).length()));

    FileManager::writeFile((std::to_string(*generation)).c_str(), *(id),
                           (std::to_string(*generation)).length());

    for(int i = 0; i < NUMBER_OF_GENES; i++)
    {
        FileManager::writeFile((std::to_string(geneticInformation->getGene(i))).c_str(), *(id),
                               ((std::to_string(geneticInformation->getGene(i)))).length());
    }

    for(int j = 0; j < NUMBER_OF_CHARACTERISTICS; j++)
    {
        FileManager::writeFile((std::to_string(*(characteristics + j))).c_str(), *(id),
                               ((std::to_string(*(characteristics + j + 1)))).length());
    }

}