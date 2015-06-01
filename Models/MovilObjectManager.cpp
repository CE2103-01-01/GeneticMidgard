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
    xml_document objectSource;
    objectSource.load_file(CONSTANT_XML_PATH);
    elementCounter = std::distance(objectSource.child("CONSTANTS").child("MOVILOBJECT").begin(),
                                   objectSource.child("CONSTANTS").child("MOVILOBJECT").end());
    listXmlData = static_cast<int*>(malloc(2*elementCounter*sizeof(int)));
    listObject = static_cast<MovilObject*>(calloc(NUMBER_OF_OBJECTS,sizeof(MovilObject)));

    xml_node temp = objectSource.child("CONSTANTS").child("MOVILOBJECT").first_child();

    for (int h = 0; h < 2*elementCounter; h+=2) {
        *(listXmlData+h) = temp.first_attribute().as_int();
        *(listXmlData+h+1)= temp.last_attribute().as_int();
        temp = temp.next_sibling();
    }
    objectSource.~xml_document();

    for(int i = 0; i<NUMBER_OF_OBJECTS; i++){
        int random = trueRandom::randRange(0,NUMBER_OF_OBJECTS-1);
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

}



/**retorna de forma random un objetos de la lista
 * @brief retorna de forma random un objeto de la lista
 * @return MovilObject
 */
MovilObject* MovilObjectManager::getRandomObject() {
    
        int rango = trueRandom::randRange(0,NUMBER_OF_OBJECTS-1);
    //std::cout<<rango<<std::endl;
        return (listObject+rango);

}


/**obtiene la instancia singleton de la clase
 * @brief obtiene la instancia singleton de la clase
 * @return MovilObjectManager*:puntero de instancia de la clase
 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
MovilObjectManager* MovilObjectManager::getInstance() {
    pthread_mutex_lock(&mutex);
    if(!instance){
        instance = static_cast<MovilObjectManager*>(malloc(sizeof(MovilObjectManager)));
        new(instance) MovilObjectManager();
    }
    pthread_mutex_unlock(&mutex);
    return instance;
}
/**Destructor de la clase
 * @brief restablecer como condicion inicial de la clase
 *
 */
MovilObjectManager::~MovilObjectManager() {
    free(listObject);
    free(listXmlData);
    instance = 0;
}