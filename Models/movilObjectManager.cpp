//
// Created by root on 30/04/15.
//

#include "movilObjectManager.h"
#include "../Network/SocketLogic.h"


using namespace pugi;
using namespace constantsSubjectXML;

movilObjectManager* movilObjectManager::instance = 0;

/**Thread
 * @brief revisa periodicamente sobre la cantidad de objectos de la lista
 */
void* managerThread(void* param){
    movilObjectManager* manager = movilObjectManager::getInstance();
    struct timespec time_controller;
    time_controller.tv_sec = 5;
    time_controller.tv_nsec = 0;
    while(*static_cast<bool*>(param)){
        if(manager->needsToUpdate()){
            manager->update();
        }
        nanosleep(&time_controller,NULL);
    }
}

/**update a la lista para rellenar objetos
 * @brief rellena el object de la lista
 */

void movilObjectManager::update(){
    movilObject* tmp = listObject+firstEmpty;
    while(tmp->isEmpty()!=-1){
        int positionOnList = tmp->getPositionOnList();
        firstEmpty = tmp->isEmpty();
        Vector2D position = Terrain::getRandomFreePosition();
        int random = trueRandom::randRange(0,elementCounter);
        new(tmp) movilObject(*(listXmlData+2*random), *(listXmlData+2*random+1), idCounter*OBJECT_ID_MULTIPLIER + OBJECT_ID,
                             position.x, position.y, positionOnList);
        tmp = listObject+firstEmpty;
    }
}

/**retorna de forma random un objetos de la lista
 * @brief retorna de forma random un objeto de la lista
 * @return movilObject
 */
movilObject* movilObjectManager::getRandomObject() {
    int objectNumber = trueRandom::getRandom()%NUMBER_OF_OBJECTS;
    return listObject+objectNumber;
}

/**obtiene la instancia singleton de la clase
 * @brief obtiene la instancia singleton de la clase
 * @return movilObjectManager*:puntero de instancia de la clase
 */
movilObjectManager* movilObjectManager::getInstance() {
    if(instance==0){
        instance = static_cast<movilObjectManager*>(malloc(sizeof(movilObjectManager)));
        new(instance) movilObjectManager();
    }
    return instance;
}
/**Constructor
 * @brief se genera objetos de forma random desde los datos de xml
 */
movilObjectManager::movilObjectManager() {
    idCounter = 0;
    objectCounter = 0;
    firstEmpty = -1;
    xml_document objectSource;
    objectSource.load_file(CONSTANT_XML_PATH);
    elementCounter = std::distance(objectSource.child("CONSTANTS").child("MOVILOBJECT").begin(),
                                       objectSource.child("CONSTANTS").child("MOVILOBJECT").end());
    listXmlData = static_cast<int*>(malloc(2*elementCounter*sizeof(int)));
    listObject = static_cast<movilObject*>(calloc(0,NUMBER_OF_OBJECTS*sizeof(movilObject)));

    xml_node temp = objectSource.child("CONSTANTS").child("MOVILOBJECT").first_child();

    for (int h = 0; h < 2*elementCounter; h+=2) {
        *(listXmlData+h) = temp.first_attribute().as_int();
        *(listXmlData+h+1)= temp.last_attribute().as_int();
        temp = temp.next_sibling();
    }
    for(int i = 0; i<NUMBER_OF_OBJECTS-1; i++){
        int random = trueRandom::getRandom()%elementCounter;
        Vector2D position = Terrain::getRandomFreePosition();
        *(listObject+i) = movilObject(*(listXmlData+2*random), *(listXmlData+2*random+1), idCounter*OBJECT_ID_MULTIPLIER + OBJECT_ID,
                                      position.x, position.y, i);
        std::cout<< (listObject+i)->getId()<< std::endl;
        std::cout<<(listObject+i)->get_X_Position()<< std::endl;
        std::cout<<(listObject+i)->get_Y_Position()<< std::endl;
        createObject((listObject+i)->getId(),(listObject+i)->get_X_Position(),(listObject+i)->get_Y_Position());
        objectCounter++;
        idCounter++;
    }

}
/**Obtiene el objeto segun la position de Vector2D
 * @brief Obtiene el objeto segun la position de Vector2D
 * @param Vector2D position: una posicion especifica
 * @return movilObject object: el objeto de la position
 */

movilObject movilObjectManager::getDataByPosistion(Vector2D position) {
    for(int i = 0; i<NUMBER_OF_OBJECTS;i++){
        movilObject* tmp = listObject+i;
        if(tmp->get_X_Position()==position.x && tmp->get_Y_Position()==position.y){
            movilObject tmp2 = *tmp;
            tmp->freeSpace(firstEmpty);
            firstEmpty=tmp->isEmpty();
            return tmp2;
        }
    }
}
/**Reduce cantidad de contador de objetos
 * @brief se reduce 1 cantidad en el contador de objetos
 */
void movilObjectManager::decreseCounter(movilObject object) {
    objectCounter--;
    int tmp = firstEmpty;
    firstEmpty = object.getPositionOnList();
    (listObject + object.getPositionOnList())->freeSpace(tmp);
}

/**@brief verifica si se requieren nuevos objetos moviles
 * @return bool
 */
bool movilObjectManager::needsToUpdate() {
    return firstEmpty != -1;
}


/**Constructor
 * @brief se crea el objeto de acuerdo de los parametros
 * @param movilOBjectManager control: referencia de Manager
 * @param string name: nombre de objeto, int carateristic:identificador de caracteristca
 * @param int value: valor que se modifica en la caracteristica
 */
movilObject::movilObject(int characteristic,int value, int identificator,int xPosition,int yPosition, int positionOnListParam)  {
    position = Vector2D(xPosition,yPosition);
    use = false;
    object = characteristic;
    effect = value;
    id=identificator;
    positionOnList = positionOnListParam;
    isEmptyVar = -1;
}

int movilObject::getPositionOnList(){
    return positionOnList;
}
/**aplica el efecto del objeto a una persona
 * @brief modifica la caracteristica correspondiente de la persona
 * @param Subject* person: referencia de una persona
 */
void movilObject::applyEffect(Subject* person) {
    if (use!=true) {
        use = true;
        person->setCharacteristic(effect,(unsigned char)object);
        Terrain::set(position,0);
        movilObjectManager::getInstance()->decreseCounter(*this);
        deleteObject(id);
    }

}
/**aplica el efecto del objeto a una persona
 * @brief modifica la caracteristica correspondiente de la persona
 * @param Subject* person: referencia de una persona
 */
int movilObject::isEmpty() {
    return isEmptyVar;

}
/**Destructor de la clase
 * @brief desctrutor de la clase
 */
movilObject::~movilObject() {
}

/**obtener el id del objeto
 *@brief obtener el id del objeto
 * @return int id:  id del objeto
 *
 */
int movilObject::getId() {
    return id;
}
/**obtener la posicion en x del objeto
 *@brief obtener el posicion en x del objeto
 * @return int :  posicion x del objeto
 *
 */
int movilObject::get_X_Position() {
    return position.x;
}
/**obtener la posicion en y del objeto
 *@brief obtener el posicion en y del objeto
 * @return int :  posicion y del objeto
 *
 */
int movilObject::get_Y_Position() {
    return position.y;
}
Vector2D movilObject::getVector() {
    return position;
}

/**SobreCargar el operator ==
 * @brief sobrecargar el operator == de la clase movilObject
 */
bool movilObject::operator==(movilObject object) {
    return position.x==object.position.x && position.y == object.position.y;
}

int movilObject::getEffect() {
    return effect;
}
int movilObject::getCharacteristic() {
    return object;
}

void movilObject::freeSpace(int nextEmptyParam){
    isEmptyVar = nextEmptyParam;
}













