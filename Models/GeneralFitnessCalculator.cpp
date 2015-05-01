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
int GeneralFitnessCalculator::calculateFitness(Chromosome chromosome) {
    int* index = static_cast<int*>(malloc(sizeof(int)));
    int fitness;
    (*index)=0;
    for(xml_attribute attrIter = constantXml.child(CONSTANT_XML_ROOT).child("Fitness").first_attribute();
        attrIter && (*index)<NUMBER_OF_CHARACTERISTICS; attrIter = attrIter.next_attribute(), (*index)++) {
       fitness+=  (attrIter.as_int()); //TODO alex: debe tomar el gen como void* y convertirlo, el tamano es GENE_LEN_ON_BYTES
    }
    free(index);
    return fitness;
}
