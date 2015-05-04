//
// Created by alex on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
#define PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H

#include "../libs/pugixml/pugixml.hpp"
#include "../Models/Chromosome.h"
#include "BinaryReader.h"
#include "../Data/DoubleList.h"

using namespace pugi;

class GeneralFitnessCalculator {
    float* constants;
    void readXML();
public:
    GeneralFitnessCalculator();
    float calculateFitness(Chromosome chromosome);

};


#endif //PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
