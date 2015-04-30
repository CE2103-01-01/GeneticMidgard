//
// Created by pablo on 20/04/15.
//


#include "Random.h"

void trueRandom::init(){
    std::srand(std::time(NULL)); //use current time as seed for random generator
}

int trueRandom::getRandom(){
    return std::rand();
}

int trueRandom::randRange(int min, int max){
    return min + (rand() % (int)(max - min + 1));
}

float trueRandom::randRange(float min, float max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}