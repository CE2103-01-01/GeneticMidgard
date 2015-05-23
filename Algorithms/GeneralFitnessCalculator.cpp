//
// Created by alex on 01/05/15.
//

#include "GeneralFitnessCalculator.h"
#include "../libs/rapidxml/rapidxml_utils.hpp"

using namespace pugi;
using namespace constantsSubjectXML;

GeneralFitnessCalculator* GeneralFitnessCalculator::instance = 0;

/**@brief constructor, lee el XML. No se debe llamar explicitamente
 */
GeneralFitnessCalculator::GeneralFitnessCalculator(){
    constants = static_cast<float*>(malloc(sizeof(float)*NUMBER_OF_GENES));
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( CONSTANT_XML_PATH );
    doc.parse<0>( file.data() );
    std::string age ="0";
    root_node = doc.first_node("CONSTANTS")->first_node("FitnessByAge")->first_node((CONSTANT_AGE + std::to_string(0)).c_str());
    int forIteratorIndex = 0;
    rapidxml::xml_node<>*node = root_node->first_node();
    while(node) {
        *(constants + forIteratorIndex++) = std::atof(node->value());
        node = node->next_sibling();
    }
    ageIdentificator = static_cast<int*>(malloc(sizeof(int)));
    *ageIdentificator = 0;
}

/**@brief calcula el fitness de un cromosoma
 * @param cromosoma
 * @return float
 */
float GeneralFitnessCalculator::calculateFitness(Chromosome* chromosome) {
    float fitness = 0;
    for(int i = 0; i < NUMBER_OF_GENES - 3; i++){
        fitness += *(constants+i) * chromosome->getGene(i);
    }
    return fitness;

}

/**@brief metodo que accede a la unica instancia
 * @return GeneralFitnessCalculator*
 */
GeneralFitnessCalculator* GeneralFitnessCalculator::getInstance(){
    if(!instance){
        //Si no hay instancia reserva el espacio correspondiente e inicializa
        instance = static_cast<GeneralFitnessCalculator*>(malloc(sizeof(GeneralFitnessCalculator)));
        new(instance) GeneralFitnessCalculator();
    }
    //Retorna la instancia, ya sea guardada o recien creada
    return instance;
}

void GeneralFitnessCalculator::changeEdda() {
    (*ageIdentificator)++;
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( CONSTANT_XML_PATH );
    doc.parse<0>( file.data() );
    root_node = doc.first_node("CONSTANTS")->first_node("FitnessByAge")->first_node((CONSTANT_AGE + std::to_string(*ageIdentificator)).c_str());
    int forIteratorIndex = 0;
    rapidxml::xml_node<>*node = root_node->first_node();
    while(node) {
        *(constants + forIteratorIndex++) = std::atof(node->value());
        node = node->next_sibling();
    }
}
