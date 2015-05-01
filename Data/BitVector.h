//
// Created by jairo-m-m on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_BITVECTOR_H
#define PROJECTMIDGARDLOGIC_BITVECTOR_H

#include "iostream"
#include "../Interface/Random.h"


class BitVector {

public:

    BitVector(size_t size); //constructor de un BitVector con un size específico

    BitVector(void* array_data, size_t size); //constructor de un BitVector con su dato y su tamaño especifico

    void set(size_t index); //setea el valor del bit accesado mediante el index

    bool get(size_t index); //retorna el valor del bit accesado mediante el index

    void setSize(size_t _size); //setea el valor del size

    size_t getSize(); //retorna el valor del size

    void setByteArray(void* array_data);

    unsigned char* getByteArray();
private:

    unsigned char* _bytearray; //data del bitvector
    size_t _size;  //tamaño del bitvector

    unsigned char Mask(); //hace una mascara para el trabajo de bits
    size_t ByteNumber(size_t index) const;
};

#endif //PROJECTMIDGARDLOGIC_BITVECTOR_H
