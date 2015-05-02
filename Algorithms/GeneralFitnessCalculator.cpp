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
long GeneralFitnessCalculator::calculateFitness(Chromosome* chromosome) {
    int* forIteratorIndex = static_cast<int*>(malloc(sizeof(int)));
    long fitness;
    (*forIteratorIndex) = 0;

    for(xml_attribute attributeIterator = constantXml.child(CONSTANT_XML_ROOT).child("Fitness").first_attribute();
        attributeIterator && (*forIteratorIndex) < NUMBER_OF_CHARACTERISTICS;
        attributeIterator = attributeIterator.next_attribute(), (*forIteratorIndex)++)
    {
        void* valueOfGene = malloc(GENE_LEN_ON_BYTES);
        BinaryReader::read(valueOfGene,GENE_LEN_ON_BYTES,BinaryReader::convertDecimal,0);
        fitness +=  attributeIterator.as_float() * (*static_cast<long*>(valueOfGene));
    }

    free(forIteratorIndex);
    return fitness;
}
