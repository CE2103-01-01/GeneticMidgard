//
// Created by pablo on 20/04/15.
//


#include "Random.h"
namespace trueRandom{
    int getRandom() {
        std::srand(std::time(0)); //use current time as seed for random generator
        return std::rand();
    }

    int randRange(int i, int i1) {
        return 0;
    }

    float randRange(float d, float d1) {
        return 0;
    }
}
