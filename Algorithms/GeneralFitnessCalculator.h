//
// Created by alex on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
#define PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H

#include "../libs/pugixml/pugixml.hpp"
#include "../Models/Chromosome.h"
#include "BinaryReader.h"

using namespace pugi;

class GeneralFitnessCalculator {
    static xml_document* constantXml;
public:
    static float calculateFitness(Chromosome* chromosome);
    static void init();
};


#endif //PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
