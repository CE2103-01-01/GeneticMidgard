//
// Created by alex on 01/05/15.
//

#include "GeneralFitnessCalculator.h"

#include "../libs/pugixml/pugixml.hpp"
#include "../Constants.h"

using namespace pugi;
using namespace constantsSubjectXML;

GeneralFitnessCalculator::GeneralFitnessCalculator() {
    constantXml.load_file(CONSTANT_XML_PATH);
}

float GeneralFitnessCalculator::calculateFitness(Chromosome* chromosome) {
    float fitness = 0;
    int forIteratorIndex = 0;

    for(xml_attribute attributeIterator = constantXml.child(CONSTANT_XML_ROOT).child("Fitness").first_attribute();
        attributeIterator && forIteratorIndex < NUMBER_OF_CHARACTERISTICS;
        attributeIterator = attributeIterator.next_attribute(), forIteratorIndex++)
    {
        fitness += attributeIterator.as_float() * (*static_cast<unsigned char*>(chromosome->getGene(forIteratorIndex)));
    }
    return fitness;
}
