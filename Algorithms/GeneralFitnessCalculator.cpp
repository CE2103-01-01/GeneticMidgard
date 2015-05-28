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
    ageIdentificator = static_cast<int*>(malloc(sizeof(int)));
    *ageIdentificator = 0;
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( CONSTANT_XML_PATH );
    doc.parse<0>( file.data() );
    root_node = doc.first_node("CONSTANTS")->first_node("FitnessByAge")->first_node((CONSTANT_AGE+std::to_string(*ageIdentificator)).c_str());;
    int forIteratorIndex = 0;
    rapidxml::xml_node<>*node = root_node->first_node();
    while(node) {
        *(constants + forIteratorIndex++) = std::atof(node->value());
        node = node->next_sibling();
    }

}

/**@brief calcula el fitness de un cromosoma
 * @param cromosoma
 * @return float
 */
float GeneralFitnessCalculator::calculateFitness(Chromosome* chromosome) {
    float fitness = 0;
    for(int i = 0; i < NUMBER_OF_GENES - 3; i++){
        //Al multiplicar la constante por el gen cumple su cometido, no es necesario dividir entre nada
        //ya que siempre se saca a factor comun y no aporta mas que un rango.
        //De esta manera, para una misma constante mayor a 5, el resultado crece con el gen
        //y para un mismo gen crece con la constante
        if(*(constants+i)>5)fitness += chromosome->getGene(i)*(*(constants+i));
        //Las unicas constantes menores a cinco son las de los genes a disminuir,
        //al hacer constante/gen, para una misma constante, el resultado aumenta conforme el gen decrece
        //ademas, para un mismo gen, el resultado aumenta conforme la constante crece
        else fitness += (*(constants+i))/chromosome->getGene(i);
    }
    //esto se puede cambiar, depende de como quiera visualizar el numero
    //pero al final da lo mismo, ya que la comparacion va a seguir dando el mismo resultado
    return fitness/100;
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
/**@brief modifica el identificador de edda
 */
void GeneralFitnessCalculator::changeEdda() {
    (*ageIdentificator)++;
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( CONSTANT_XML_PATH );
    doc.parse<0>( file.data() );
    root_node = doc.first_node("CONSTANTS")->first_node("FitnessByAge")->first_node((CONSTANT_AGE+std::to_string(*ageIdentificator)).c_str());
    int forIteratorIndex = 0;
    rapidxml::xml_node<>*node = root_node->first_node();
    while(node) {
        *(constants + forIteratorIndex++) = std::atof(node->value());
        node = node->next_sibling();
    }
}
