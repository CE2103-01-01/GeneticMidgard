//
// Created by root on 30/04/15.
//

#include "movilObjectManager.h"


using namespace pugi;
using namespace constantsSubjectXML;

/**Constructor
 * @brief se genera objetos de forma random desde los datos de xml
 */
movilObjectManager::movilObjectManager() {
    xml_document objectSource;
    objectSource.load_file(CONSTANT_XML_PATH);
    listObject = DoubleList<movilObject>();
    listXmlData = DoubleList<xml_node>();
    int elementCounter=std::distance(objectSource.child("CONSTANTS").child("MOVILOBJECT").begin(),
                                     objectSource.child("CONSTANTS").child("MOVILOBJECT").end());
    xml_node temp = objectSource.child("CONSTANTS").child("MOVILOBJECT").first_child();
    listXmlData.append(temp);
    for(int h=0; h<elementCounter;h++){
        temp = temp.next_sibling();
        listXmlData.append(temp);
    }
    for(int i =0; i<500;i++){
        int objectNumber = trueRandom::randRange(0,elementCounter);

        Vector2D position = Terrain::getRandomFreePosition();
        std::string name = (*listXmlData.getNode(objectNumber)->getData()).attribute("name").as_string();
        movilObject object = movilObject(this,name,(*listXmlData.getNode(objectNumber)->getData())
                                                 .attribute("characteristic")
                                                 .as_int(),(*listXmlData.getNode(objectNumber)->getData())
                                                 .attribute("value").as_int(),i,position.x
                                                    ,position.y);
        listObject.append(object);
        Terrain::set(position,-100);
    }



    std::cout<<elementCounter<<std::endl;
}
/**Reduce cantidad de contador de objetos
 * @brief se reduce 1 cantidad en el contador de objetos
 */
void movilObjectManager::decreseCounter() {
    objectCounter--;
}
/**Constructor
 * @brief se crea el objeto de acuerdo de los parametros
 * @param movilOBjectManager control: referencia de Manager
 * @param string name: nombre de objeto, int carateristic:identificador de caracteristca
 * @param int value: valor que se modifica en la caracteristica
 */
movilObject::movilObject(movilObjectManager* control,std::string name,int characteristic,int value,
                         int identificator,int xPosition,int yPosition)  {
    manager = control;
    position=new Vector2D(xPosition,yPosition);
    use = false;
    type=name;
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
    }
    
}
/**Destructor de la clase
 * @brief desctrutor de la clase
 */
movilObject::~movilObject() {
}
/**obtener el nombre del objeto
 * @brief obtener el nombre del objeto
 * @return string:nombre del objeto
 */
std::string movilObject::getType() {
    return type;
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