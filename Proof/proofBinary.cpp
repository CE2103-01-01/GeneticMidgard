//
// Created by roberto on 27/04/15.
//

#include "proofBinary.h"

void proofBinary(){
    unsigned int getval;
    unsigned char a, b;
    std::cout << "Enter a number between 0 and 255: ";
    std::cin >> getval; a = getval;
    PR("a in binary: ", a);
    std::cout << "Enter a number between 0 and 255: ";
    std::cin >> getval; b = getval;
    PR("b in binary: ", b);
    PR("a | b = ", a | b);
    PR("a & b = ", a & b);
    PR("a ^ b = ", a ^ b);
    PR("~a = ", ~a);
    PR("~b = ", ~b);
    // An interesting bit pattern:
    unsigned char c = 0x5A;
    PR("c in binary: ", c);
    a |= c;
    PR("a |= c; a = ", a);
    b &= c;
    PR("b &= c; b = ", b);
    b ^= a;
    PR("b ^= a; b = ", b);
}
