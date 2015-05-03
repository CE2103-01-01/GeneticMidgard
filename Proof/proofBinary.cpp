//
// Created by roberto on 27/04/15.
//

#include "proofBinary.h"

void proofBinaryReader(){
    void* tmpResult = malloc(sizeof(int));

    for (int i = 0; i < 1000; i++) {
        *static_cast<int*>(tmpResult) = 0;
        BinaryReader::read((void*)&i,sizeof(i),BinaryReader::convertDecimal,tmpResult);
        std::cout << *static_cast<int*>(tmpResult) << std::endl;
    }

    free(tmpResult);
}