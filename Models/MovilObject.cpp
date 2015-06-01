//
// Created by roberto on 31/05/15.
//

#include "MovilObject.h"
#include "MovilObjectManager.h"
#include "../Network/SocketLogic.h"

/**Constructor
 * @brief se crea el objeto de acuerdo de los parametros
 * @param movilOBjectManager control: referencia de Manager
 * @param string name: nombre de objeto, int carateristic:identificador de caracteristca
 * @param int value: valor que se modifica en la caracteristica
 */
MovilObject::MovilObject(int characteristic,int value, int identificator,int xPosition,int yPosition, int positionOnListParam)  {
    position = Vector2D(xPosition,yPosition);
    use = false;
    object = characteristic;
    effect = value;
    id=identificator;
    positionOnList = positionOnListParam;
    isEmptyVar = -1;
    Terrain::set(position,id);
}

int MovilObject::getPositionOnList(){
    return positionOnList;
}
/**aplica el efecto del objeto a una persona
 * @brief modifica la caracteristica correspondiente de la persona
 * @param Subject* person: referencia de una persona
 */
void MovilObject::applyEffect(Subject* person) {
    if (use!=true) {
        use = true;
        person->setCharacteristic(effect,(unsigned char)object);
        Terrain::set(position,0);
        MovilObjectManager::getInstance()->decreseCounter(*this);
        deleteObject(id);
    }

}
/**aplica el efecto del objeto a una persona
 * @brief modifica la caracteristica correspondiente de la persona
 * @param Subject* person: referencia de una persona
 */
int MovilObject::isEmpty() {
    return isEmptyVar;

}
/**obtener el id del objeto
 *@brief obtener el id del objeto
 * @return int id:  id del objeto
 *
 */
int MovilObject::getId() {
    return id;
}
/**obtener la posicion en x del objeto
 *@brief obtener el posicion en x del objeto
 * @return int :  posicion x del objeto
 *
 */
int MovilObject::get_X_Position() {
    return position.x;
}
/**obtener la posicion en y del objeto
 *@brief obtener el posicion en y del objeto
 * @return int :  posicion y del objeto
 *
 */
int MovilObject::get_Y_Position() {
    return position.y;
}
Vector2D MovilObject::getVector() {
    return position;
}

/**SobreCargar el operator ==
 * @brief sobrecargar el operator == de la clase MovilObject
 */
bool MovilObject::operator==(MovilObject object) {
    return position.x==object.position.x && position.y == object.position.y;
}

int MovilObject::getEffect() {
    return effect;
}
int MovilObject::getCharacteristic() {
    return object;
}

void MovilObject::freeSpace(int nextEmptyParam){
    isEmptyVar = nextEmptyParam;
}


