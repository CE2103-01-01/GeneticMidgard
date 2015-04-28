//
// Created by pablo on 20/04/15.
//


#include "Random.h"

namespace trueRandom{
    void init()
    {
        std::srand(std::time(0)); //use current time as seed for random generator
    }
    int getRandom() {
        return std::rand();
    }

    int randRange(int min, int max) {
        return min + (rand() % (int)(max - min + 1));
    }

    float randRange(float min, float max) {
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }
}
