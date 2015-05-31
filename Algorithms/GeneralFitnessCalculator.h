//
// Created by alex on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
#define PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H

#include "../Models/Chromosome.h"
#include "BinaryReader.h"
#include "../Data/DoubleList.h"
#include "../libs/rapidxml/rapidxml_utils.hpp"

class GeneralFitnessCalculator {
    int* constantsTotal;
    float* constants;
    int* ageIdentificator;
    static GeneralFitnessCalculator* instance;
public:
    GeneralFitnessCalculator();
    void changeEdda();
    float calculateFitness(Chromosome* chromosome);
    static GeneralFitnessCalculator* getInstance();
};


#endif //PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
