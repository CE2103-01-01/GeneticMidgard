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
    int elementCounter=std::distance(objectSource.child("CONSTANTS").child("MOVILOBJECT").begin(),
                                     objectSource.child("CONSTANTS").child("MOVILOBJECT").end());
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
movilObject::movilObject(movilObjectManager* control,std::string name,int caracteristic,int value)  {
    manager = control;
    use = false;
    type=name;
    object = caracteristic;
    effect = value;
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
 * @return string:nombre de objeto
 */
std::string movilObject::getType() {
    return type;
}