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
int GeneralFitnessCalculator::calculateFitness(Chromosome* chromosome) {
    int* forIteratorIndex = static_cast<int*>(malloc(sizeof(int)));
    int fitness=0;
    (*forIteratorIndex)=0;
    for(xml_attribute attributeIterator = constantXml.child(CONSTANT_XML_ROOT).child("Fitness").first_attribute();
        attributeIterator && (*forIteratorIndex) < NUMBER_OF_CHARACTERISTICS;
        attributeIterator = attributeIterator.next_attribute(), (*forIteratorIndex)++)
    {
        int valor = *static_cast<unsigned char*>(chromosome->getGene(*forIteratorIndex));
        fitness+=  attributeIterator.as_float() * valor;
    }

    free(forIteratorIndex);
    return fitness;
}
