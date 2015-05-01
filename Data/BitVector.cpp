//
// Created by jairo-m-m on 29/04/15.
//

#include "BitVector.h"

/**
 * @brief Constructor del Bitvector
 * @param size: tamaño del bitvector
 * Se setea el tamaño del bitvector
 * y se reserva la memoria del dato que se va a utilizar
 * se castea el dato a unsigned char* para un manejo mas sencillo de operaciones en los bits
 */
BitVector::BitVector(size_t size)
{
    _size = (size + 7)/8;
    _bytearray = new unsigned char [_size];
    if (_bytearray == 0)
    {
        std::cerr << "** BitVector memory allocation failure -- terminating program.\n";
        exit (EXIT_FAILURE);
    }
    for (size_t i = 0; i < _size; ++i)
        _bytearray[i] = 0x00;
}

/**
 * @brief Constructor del BitVector
 * @param array_data: array de bytes-bits que se necesitan guardar para su manejo
 * @param size: tamaño del array_data
 * Se setea el tamaño del bitvector
 * Se setea el arraybits del bitvector al arraydata, y se castea a
 * unsigned char* para un manejo mas sencillo de operaciones en los bits
 */
BitVector::BitVector(void * array_data, size_t size) {}

/**
 * @brief setea valor a un bit exacto
 * @param index: indice al bit que quiere accesar
 */
void BitVector::set(size_t index)
{
    unsigned char maskbit = 1; // se crea mascara equivalente a 00000001
    maskbit = maskbit << index%8; //se hace operación de corrimiento en la mascara hasta el bit que se necesita cambiar, ej: 00010000
    this->_bytearray[ByteNumber(index)] = this->_bytearray[ByteNumber(index)] ^ maskbit; //hace operación de XOR entre el bit del bitvector y el maskbit
}

/**
 * @brief obtiene el bit que se encuentra en ese indice
 * si este es un 1 return true si es 0 returna false
 * @return true-false dependiendo del bit
 */
bool BitVector::get(size_t index)
{

    unsigned char maskbit = 1; // se crea mascara equivalente a 00000001
    maskbit = maskbit << index%8; //se hace operación de corrimiento en la mascara hasta el bit que se necesita cambiar, ej: 00010000
    if ((this->_bytearray[ByteNumber(index)] & maskbit) != 0)
        return true;
    else
        return false;
}

/**
 * @brief hace una un char y utiliza su equivalente ea 1byte para hacer operaciones de bitwise
 * @return retorna la mascara a utilizar, la cual es un unsigned char
 */
unsigned char BitVector::Mask()
{
    unsigned char mask = trueRandom::randRange(0,255);
    return mask;
}

/**
 * @brief setea el tamaño del bitvector
 * @param _size: valor del tamaño a setear
 */
void BitVector::setSize(size_t _size)
{
    this->_size = _size;
}

/**
 * @return retorna tamaño del bitvector
 */
size_t BitVector::getSize()
{
    return this->_size;
}

size_t BitVector::ByteNumber(size_t index) const
{
    index = index >> 3;
    return index;
}
