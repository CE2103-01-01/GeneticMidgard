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
    objectSource.load_file("object.xml");
    int elementCounter=std::distance(objectSource.child("MOVILOBJECT").begin(),objectSource.child("MOVILOBJECT").end());
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
    xml_document objectDocument;
    objectDocument.load_file(CONSTANT_XML_PATH);
   objectDocument.child("movilObject").attributes();
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
        if (object == 0) {


        }
        else if(object==1){

        }
        else if(object==2){

        }
        else if(object==3){

        }
        else if(object==4){

        }
        else if(object==5){

        }
        else if(object==6){

        }
        else if(object==7){

        }
        else if(object==8){

        }
        else if(object==9){

        }


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