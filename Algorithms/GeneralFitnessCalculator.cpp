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

GeneralFitnessCalculator::~GeneralFitnessCalculator(){
    free(constants);
}

void GeneralFitnessCalculator::readXML() {
    constants = static_cast<float*>(malloc(sizeof(float)*Chromosome::readLenghtFromXML()));

    numberOfGenes = static_cast<int*>(malloc(sizeof(int)));
    *numberOfGenes = Chromosome::readLenghtFromXML();

    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( CONSTANT_XML_PATH );
    doc.parse<0>( file.data() );
    root_node = doc.first_node("CONSTANTS")->first_node("Fitness");
    int forIteratorIndex = 0;
    //TODO: agregar a constante
    for( rapidxml::xml_node<>*node = root_node->first_node();
         node;
         node = node->next_sibling() ) {
        {
            *(constants + forIteratorIndex * sizeof(float)) = std::atof(node->value());
        }
    }
}


float GeneralFitnessCalculator::calculateFitness(Chromosome* chromosome) {
    float fitness = 0;
    for(int i = 0; i<*numberOfGenes; i++){
        fitness += (*(constants+i*sizeof(float))) * (*static_cast<unsigned char*>(chromosome->getGene(i)));
    }
    return fitness;

}
