//
// Created by alex on 01/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
#define PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H

#include "../libs/pugixml/pugixml.hpp"
#include "../Models/Chromosome.h"

using namespace pugi;

class GeneralFitnessCalculator {
    xml_document constantXml;
public:
    GeneralFitnessCalculator();
    int calculateFitness(Chromosome chromosome);

};


#endif //PROJECTMIDGARDLOGIC_GENERALFITNESSCALCULATOR_H
