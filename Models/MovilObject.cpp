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
    position_x = xPosition;
    position_y = yPosition;
    use = false;
    object = characteristic;
    effect = value;
    id=identificator;

    Terrain::set(Vector2D(xPosition,yPosition),id);
}

/**aplica el efecto del objeto a una persona
 * @brief modifica la caracteristica correspondiente de la persona
 * @param Subject* person: referencia de una persona
 */
void MovilObject::applyEffect(Subject* person) {
    if (use!=true) {
        use = true;
        person->setCharacteristic(effect,(unsigned char)object);
        Terrain::set(Vector2D(position_x,position_y),0);
        Vector2D newPosition =Terrain::getRandomFreePosition();
        position_x = newPosition.x;
        position_y = newPosition.y;
        use = true;
        Terrain::set(Vector2D(position_x,position_y),id);
        //updateObject(id,position_x,position_y);
    }

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
    return position_x;
}
/**obtener la posicion en y del objeto
 *@brief obtener el posicion en y del objeto
 * @return int :  posicion y del objeto
 *
 */
int MovilObject::get_Y_Position() {
    return position_y;
}
Vector2D MovilObject::getVector() {
    return Vector2D(position_x,position_y);
}

/**SobreCargar el operator ==
 * @brief sobrecargar el operator == de la clase MovilObject
 */
bool MovilObject::operator==(MovilObject object) {
    return position_x==object.position_x && position_y == object.position_y;
}

int MovilObject::getEffect() {
    return effect;
}
int MovilObject::getCharacteristic() {
    return object;
}



