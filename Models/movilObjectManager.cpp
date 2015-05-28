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
    for(int i=listObject.len();i<listSize;i++){
        int objectNumber = trueRandom::randRange(0,listXmlData.len());
        Vector2D position = Terrain::getRandomFreePosition();
        movilObject object = movilObject(this, (*listXmlData.getNode(objectNumber)->getData())
                .attribute("characteristic")
                .as_int(), (*listXmlData.getNode(objectNumber)->getData())
                                                 .attribute("value").as_int(), idCounter*OBJECT_ID_MULTIPLIER + OBJECT_ID,
                                         position.x, position.y);
        listObject.append(object);
        Terrain::set(position, object.getId());
        objectCounter++;
        idCounter++;
    }
}

/**retorna de forma random un objetos de la lista
 * @brief retorna de forma random un objeto de la lista
 * @return movilObject
 */
movilObject* movilObjectManager::getRandomObject() {
    int objectNumber = trueRandom::randRange(0,listObject.len());
    return (listObject.getNode(objectNumber)->getData());
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
    int elementCounter = std::distance(objectSource.child("CONSTANTS").child("MOVILOBJECT").begin(),
                                       objectSource.child("CONSTANTS").child("MOVILOBJECT").end());
    xml_document objectSource;
    objectSource.load_file(CONSTANT_XML_PATH);
    listXmlData = static_cast<int*>(malloc(2*elementCounter*sizeof(int)));
    listObject = static_cast<movilObject*>(calloc(0,30*sizeof(movilObject)));



    objectCounter = 0;
    xml_node temp = objectSource.child("CONSTANTS").child("MOVILOBJECT").first_child();


    for (int h = 0; h < 2*elementCounter; h+=2) {

        *(listXmlData+h) = temp.first_attribute().as_int();
        *(listXmlData+h+1)= temp.last_attribute().as_int();
        temp = temp.next_sibling();
    }
        for (int i = 0; i < elementCounter; i++,  idCounter) {
            Vector2D position = Terrain::getRandomFreePosition();
            int Effect =*(listXmlData+2*i);


            std::cout<<"Effect "<<Effect<<std::endl;
            int characteristic = *(listXmlData+2*i+1);
            std::cout<<"Characteristic "<<characteristic<<std::endl;

            movilObject object = movilObject(this,characteristic , Effect, idCounter*OBJECT_ID_MULTIPLIER + OBJECT_ID,
                                                      position.x, position.y);

            std::cout<<"hola pablo"<<std::endl;
            createObject(object.getId(),object.get_X_Position(),object.get_Y_Position());
            Terrain::set(position, object.getId());
            objectCounter++;
            idCounter++;
        }
        listSize = listObject.len();

    for(int i =0;i<listObject.len();i++){
        std::cout<<"Object ID "<<listObject.getNode(i)->getData()->getId()<<std::endl;
        std::cout<<"Object Object "<<listObject.getNode(i)->getData()->getCharacteristic()<<std::endl;
        std::cout<<"Object Effect "<<listObject.getNode(i)->getData()->getEffect()<<std::endl;
    }

        std::cout << elementCounter << std::endl;

}
/**Obtiene el objeto segun la position de Vector2D
 * @brief Obtiene el objeto segun la position de Vector2D
 * @param Vector2D position: una posicion especifica
 * @return movilObject object: el objeto de la position
 */

movilObject movilObjectManager::getDataByPosistion(Vector2D position) {
    for(int i = 0; i<listObject.len();i++){
        if(listObject.get(i)->get_X_Position()==position.x && listObject.get(i)->get_Y_Position()==position.y){
            movilObject object = *listObject.get(i);
            listObject.deleteNodeByData(*listObject.get(i));
            return object;
        }
    }
}
/**Reduce cantidad de contador de objetos
 * @brief se reduce 1 cantidad en el contador de objetos
 */
void movilObjectManager::decreseCounter(movilObject object) {
    objectCounter--;
    listObject.deleteNodeByData(object);
}

/**@brief verifica si se requieren nuevos objetos moviles
 * @return bool
 */
bool movilObjectManager::needsToUpdate() {
    return listSize > listObject.len();
}


/**Constructor
 * @brief se crea el objeto de acuerdo de los parametros
 * @param movilOBjectManager control: referencia de Manager
 * @param string name: nombre de objeto, int carateristic:identificador de caracteristca
 * @param int value: valor que se modifica en la caracteristica
 */
movilObject::movilObject(movilObjectManager* control,int characteristic,int value,
                         int identificator,int xPosition,int yPosition)  {
    manager = control;
    position=new Vector2D(xPosition,yPosition);
    use = false;
    object = characteristic;
    effect = value;
    id=identificator;
}
/**aplica el efecto del objeto a una persona
 * @brief modifica la caracteristica correspondiente de la persona
 * @param Subject* person: referencia de una persona
 */
void movilObject::applyEffect(Subject* person) {
    if (use!=true) {
        use = true;
        person->setCharacteristic(effect,(unsigned char)object);
        Terrain::set(*position,0);
        manager->decreseCounter(*this);
        deleteObject(id);
    }

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
    return position->x;
}
/**obtener la posicion en y del objeto
 *@brief obtener el posicion en y del objeto
 * @return int :  posicion y del objeto
 *
 */
int movilObject::get_Y_Position() {
    return position->y;
}
Vector2D* movilObject::getVector() {
    return position;
}

/**SobreCargar el operator ==
 * @brief sobrecargar el operator == de la clase movilObject
 */
bool movilObject::operator==(movilObject object) {
    return position->x==object.position->x && position->y == object.position->y;
}

int movilObject::getEffect() {
    return effect;
}
int movilObject::getCharacteristic() {
    return object;
}

















