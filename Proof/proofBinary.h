//
// Created by roberto on 27/04/15.
//

#ifndef PROJECTMIDGARD_PROOFBINARY_H
#define PROJECTMIDGARD_PROOFBINARY_H

#include "../Algorithms/printBinary.h"

#define PR(STR, EXPR) \
  std::cout << STR; printBinary(EXPR); std::cout << std::endl;

void proofBinary();

#endif //PROJECTMIDGARD_PROOFBINARY_H
