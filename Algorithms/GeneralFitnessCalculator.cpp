//
// Created by alex on 01/05/15.
//

#include "GeneralFitnessCalculator.h"
#include "../libs/rapidxml/rapidxml_utils.hpp"

using namespace pugi;
using namespace constantsSubjectXML;

GeneralFitnessCalculator::GeneralFitnessCalculator(){
    readXML();
}

void GeneralFitnessCalculator::readXML() {
    constants = static_cast<float*>(malloc(sizeof(float)*NUMBER_OF_GENES));

    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( CONSTANT_XML_PATH );
    doc.parse<0>( file.data() );
    root_node = doc.first_node("CONSTANTS")->first_node("Fitness");
    int forIteratorIndex = 0;
    //TODO: agregar a constante
    rapidxml::xml_node<>*node = root_node->first_node();

    while(node)
    {
        *(constants + forIteratorIndex++) = std::atof(node->value());
        node = node->next_sibling();
    }
}


float GeneralFitnessCalculator::calculateFitness(Chromosome chromosome) {
    float fitness = 0;
    for(int i = 0; i < NUMBER_OF_GENES; i++){
        fitness += *(constants+i) * (*chromosome.getGene(i));
    }
    return fitness;

}
