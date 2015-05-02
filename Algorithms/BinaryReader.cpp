//
// Created by roberto on 01/05/15.
//

#include "BinaryReader.h"

/**@brief: lee bit a bit y ejecuta un metodo
 * @param void* toReed: puntero al dato a leer
 * @param int sizeToReed: tamano en bytes del puntero
 * @param void* method(bool, void*, int, int): metodo a ejecutar, debe recibir bit a bit
 *                    @param bool: si el bit es 0 se envia false, si es 1 se envia true
 *                    @param void* parametro extra por si se requiere
 *                    @param int byte actual
 *                    @param int biy actual
 * @param void* parameter
 */
void BinaryReader::read(void* toReed, int sizeToReed, void* method(bool, void*, int, int), void* parameter){
    //Itera sobre los bytes
    for (int i = 0; i < sizeToReed; i++) {
        //Itera sobre los bits
        for(int j = 0; j < 8; j++){
            if(*static_cast<unsigned char*>(toReed + i) & (1 << j))
                //Si el bit es 1 envia true
                method(true, parameter, i, j);
            else
                //Si el bit es 0 envia false
                method(false, parameter, i, j);
        }
    }
}

/**@brief: metodo que imprime 1 o 0, segun sea el booleano que reciba
 * @param bool numberToRead: valor booleano del bit
 * @param void* variableToUpdate: variable a cambiar, si se debe
 * @param int byteToRead: byte actual de la cadena
 * @param int bitToRead: bit actual de la cadena
 */
void* BinaryReader::printBinary(bool numberToRead,  void* variableToUpdate, int byteToRead, int bitToRead){
    if(numberToRead) {
        std::cout << "1";
    }else{
        std::cout << "0";
    }
}

/**@brief:
 * @param bool numberToRead: valor booleano del bit
 * @param void* variableToUpdate: variable a cambiar, si se debe
 * @param int byteToRead: byte actual de la cadena
 * @param int bitToRead: bit actual de la cadena
 */
void* BinaryReader::convertDecimal(bool numberToRead,  void* variableToUpdate, int byteToRead, int bitToRead){
    if(numberToRead) {
        *static_cast<int*>(variableToUpdate) +=  pow(2 , ((byteToRead)*8 + bitToRead));
    }
}