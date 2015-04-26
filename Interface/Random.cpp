//
// Created by pablo on 20/04/15.
//


#include "Random.h"
namespace trueRandom{
    int getRandom() {
        std::srand(std::time(0)); //use current time as seed for random generator
        return std::rand();
    }

    int randRange(int min, int max) {
        return min + (rand() % (int)(max - min + 1));
    }

    float randRange(float min, float max) {
        return min + (rand() % (int)(max - min + 1));//TODO-pablo check si funciona
    }
}
