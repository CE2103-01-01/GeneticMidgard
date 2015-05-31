//
// Created by roberto on 25/05/15.
//

#include "God.h"

/**@brief Constructor
 * @param unsigned char id: identificacion
 */
God::God() {
    //Reserva espacio para los genes
    attributes = static_cast<unsigned char*>(malloc(NUMBER_OF_ATTRIBUTES));
    //Itera llenando los atributos
    for(int i = 0; i < NUMBER_OF_ATTRIBUTES; i++){
        //Llena los genes con valores random entre 200 y 255
        *(attributes + i) = trueRandom::getRandom()%56 + 200;
    }
    *(attributes + POSITION_OF_GOD_ATTRIBUTE_GENERAL_COLOR) = 255;
}

/**@brief Constructor de copia
 * @param const God& other: dios a copiar
 */
God::God(const God& other){
    //Reserva espacio para los genes
    attributes = static_cast<unsigned char*>(malloc(NUMBER_OF_ATTRIBUTES));
    //Itera llenando los atributos
    for(int i = 0; i < NUMBER_OF_ATTRIBUTES; i++){
        //Copia los genes del otro sujeto
        *(attributes + i) = *(other.attributes+i);
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
    //Comprueba si el valor que se va a restar sacaria al atributo de rango hacia el negativo
    if(*(attributes+POSITION_OF_GOD_ATTRIBUTE_LIFE) <= value){
        //Si sacaria al atributode rango, lo coloca en 0
        *(attributes+POSITION_OF_GOD_ATTRIBUTE_LIFE) = 0;
    }else{
        //Si no sacaria al atributo de rango, le resta el valor
        *(attributes+POSITION_OF_GOD_ATTRIBUTE_LIFE)-= value;
    }
}