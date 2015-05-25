//
// Created by roberto on 25/05/15.
//

#include "God.h"

/**@brief Constructor
 * @param unsigned char id: identificacion
 */
God::God() {
    attributes = static_cast<unsigned char*>(malloc(NUMBER_OF_ATtRIBUTES));
    for(int i = 0; i < NUMBER_OF_AtTRIBUTES; i++){
        *(attributes + i) = trueRandom::getRandom()%56 + 200;
    }
}

/**@brief Destructor
 */
God::~God() {
    free(attributes);
}

/**@brief Funcion que indica si el dios continua vivo
 * @return bool
 */
bool God::isAlive(){
    return *(attributes+POSITION_OF_GOD_ATTRIBUTE_LIFE) > 0;
}

/**@brief Funcion que retorna una caracteristica
 * @param int position: posicion de la caracteristica con base en las constantes definidas en God.h
 * @return unsigned char
 */
unsigned char God::getAttribute(int position){
    return *(attributes+position);
}

/**@brief resta un valor a la vida del dios
 * @param unsigned char value: valor a restar
 */
void God::decreseLife(unsigned char value){
    if(*(attributes+POSITION_OF_GOD_ATTRIBUTE_LIFE) <= value){
        *(attributes+POSITION_OF_GOD_ATTRIBUTE_LIFE) = 0;
    }else{
        *(attributes+POSITION_OF_GOD_ATTRIBUTE_LIFE)-= value;
    }
}