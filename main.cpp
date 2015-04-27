#include <iostream>
#include "Data/TreeProof.h"
#include "Interface/Random.h"
#include "Models/Terrain.h"

#define PR(STR, EXPR) \
  cout << STR; printBinary(EXPR); cout << endl;
using namespace std;

void printBinary(const unsigned char val);

int main()
{
    Terrain::initArray();

    unsigned int getval;
    unsigned char a, b;
    cout << "Enter a number between 0 and 255: ";
    cin >> getval; a = getval;
    PR("a in binary: ", a);
    cout << "Enter a number between 0 and 255: ";
    cin >> getval; b = getval;
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

    /*short signed cero = 0, uno = 1, dos = 2;

    cout << "~0 == " << ~cero << endl;
    cout << "~1 == " << ~uno << endl;
    cout << "~2 == " << ~dos << endl;*/
    return 0;
}

void printBinary(const unsigned char val) {
    for(int i = 7; i >= 0; i--){
        if(val & (1 << i))
            std::cout << "1";
        else
            std::cout << "0";
    }
} ///:~