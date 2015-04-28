//
// Created by roberto on 27/04/15.
//

#include "printBinary.h"

void printBinary(const unsigned char val){
    for(int i = 7; i >= 0; i--){
        if(val & (1 << i))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << " ";
}