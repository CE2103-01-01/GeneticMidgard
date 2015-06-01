//
// Created by root on 30/04/15.
//

#include "MovilObjectManager.h"
#include "../Network/SocketLogic.h"
#include "../libs/pugixml/pugixml.hpp"
#include "PopulationManager.h"


using namespace pugi;
using namespace constantsSubjectXML;

MovilObjectManager* MovilObjectManager::instance = 0;

/**Constructor
 * @brief se genera objetos de forma random desde los datos de xml
 */
MovilObjectManager::MovilObjectManager() {
    idCounter = 0;
    objectCounter = 0;
    firstEmpty = -1;
    xml_document objectSource;
    objectSource.load_file(CONSTANT_XML_PATH);
    elementCounter = std::distance(objectSource.child("CONSTANTS").child("MOVILOBJECT").begin(),
                                   objectSource.child("CONSTANTS").child("MOVILOBJECT").end());
    listXmlData = static_cast<int*>(malloc(2*elementCounter*sizeof(int)));
    listObject = static_cast<MovilObject*>(calloc(0,NUMBER_OF_OBJECTS*sizeof(MovilObject)));

    xml_node temp = objectSource.child("CONSTANTS").child("MOVILOBJECT").first_child();

    for (int h = 0; h < 2*elementCounter; h+=2) {
        *(listXmlData+h) = temp.first_attribute().as_int();
        *(listXmlData+h+1)= temp.last_attribute().as_int();
        temp = temp.next_sibling();
    }
    objectSource.~xml_document();
    for(int i = 0; i<NUMBER_OF_OBJECTS-1; i++){
        int random = trueRandom::getRandom()%elementCounter;
        Vector2D position = Terrain::getRandomFreePosition();
        *(listObject+i) = MovilObject(*(listXmlData+2*random), *(listXmlData+2*random+1), idCounter*OBJECT_ID_MULTIPLIER + OBJECT_ID,
                                      position.x, position.y, i);
        MovilObject* object = (listObject+i);
        int id = object->getId();
        int x_position =  object->get_X_Position();
        int y_position =  object->get_Y_Position();
        createObject(id,x_position,y_position);
        objectCounter++;
        idCounter++;
    }
    updateThread = static_cast<pthread_t *>(malloc(sizeof(pthread_t)));
    pthread_create(updateThread,NULL,managerThread,NULL);
}


/**Destructor
 */
MovilObjectManager::~MovilObjectManager(){
    free(updateThread);
}


/**update a la lista para rellenar objetos
 * @brief rellena el object de la lista
 */
void MovilObjectManager::update(){
    MovilObject* tmp = listObject+firstEmpty;
    while(tmp->isEmpty()!=-1){
        int positionOnList = tmp->getPositionOnList();
        firstEmpty = tmp->isEmpty();
        Vector2D position = Terrain::getRandomFreePosition();
        int random = trueRandom::randRange(0,elementCounter);
        new(tmp) MovilObject(*(listXmlData+2*random), *(listXmlData+2*random+1), idCounter*OBJECT_ID_MULTIPLIER + OBJECT_ID,
                             position.x, position.y, positionOnList);
        tmp = listObject+firstEmpty;
    }
}


/**retorna de forma random un objetos de la lista
 * @brief retorna de forma random un objeto de la lista
 * @return MovilObject
 */
MovilObject* MovilObjectManager::getRandomObject() {
    if(firstEmpty!=-1){
        MovilObject* tmp = listObject+firstEmpty;
        firstEmpty = tmp->isEmpty();
        return tmp;
    }else{
        return listObject+trueRandom::getRandom()%NUMBER_OF_OBJECTS;
    }
}


/**obtiene la instancia singleton de la clase
 * @brief obtiene la instancia singleton de la clase
 * @return MovilObjectManager*:puntero de instancia de la clase
 */
MovilObjectManager* MovilObjectManager::getInstance() {
    if(instance==0){
        instance = static_cast<MovilObjectManager*>(malloc(sizeof(MovilObjectManager)));
        new(instance) MovilObjectManager();
    }
    return instance;
}


/**Obtiene el objeto segun la position de Vector2D
 * @brief Obtiene el objeto segun la position de Vector2D
 * @param Vector2D position: una posicion especifica
 * @return MovilObject object: el objeto de la position
 */
MovilObject MovilObjectManager::getDataByPosistion(Vector2D position) {
    for(int i = 0; i<NUMBER_OF_OBJECTS;i++){
        MovilObject* tmp = listObject+i;
        if(tmp->get_X_Position()==position.x && tmp->get_Y_Position()==position.y){
            MovilObject tmp2 = *tmp;
            tmp->freeSpace(firstEmpty);
            firstEmpty=tmp->isEmpty();
            return tmp2;
        }
    }
}
/**Reduce cantidad de contador de objetos
 * @brief se reduce 1 cantidad en el contador de objetos
 */
void MovilObjectManager::decreseCounter(MovilObject object) {
    objectCounter--;
    int tmp = firstEmpty;
    firstEmpty = object.getPositionOnList();
    (listObject + object.getPositionOnList())->freeSpace(tmp);
}

/**@brief verifica si se requieren nuevos objetos moviles
 * @return bool
 */
bool MovilObjectManager::needsToUpdate() {
    return firstEmpty != -1;
}



/**Thread
 * @brief revisa periodicamente sobre la cantidad de objectos de la lista
 */
void* managerThread(void* param){
    MovilObjectManager* manager = MovilObjectManager::getInstance();
    struct timespec time_controller;
    time_controller.tv_sec = 5;
    time_controller.tv_nsec = 0;
    while(PopulationManager::getInstance()->getActivePopulations()){
        if(manager->needsToUpdate()) manager->update();
        nanosleep(&time_controller,NULL);
    }
}