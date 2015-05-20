//
// Created by roberto on 27/04/15.
//

#include "ChromosomeMixer.h"

/* Mezclador de cromosomas
 * @brief: Recibe la informacion genetica de dos individuos, la mezcla y retorna dos
 *         individuos que se accesan mediante aritmetica de punteros
 * @param: Chromosome* fatherGeneticInformation: cromosoma del padre
 * @param: Chromosome* motherGeneticInformation: cromosoma de la madre
 * @return Chromosome*: dos cromosomas hijos, (return) & (return + sizeof(Chromosome))
 */
Chromosome* ChromosomeMixer::mix(Chromosome* fatherGeneticInformation, Chromosome* motherGeneticInformation){
    //Mezcla cromosomas
    unsigned char* newGeneticMaterialOne = static_cast<unsigned char*>(malloc(constantsSubjectXML::NUMBER_OF_GENES));
    unsigned char* newGeneticMaterialTwo = static_cast<unsigned char*>(malloc(constantsSubjectXML::NUMBER_OF_GENES));
    for(int i=0; i < constantsSubjectXML::NUMBER_OF_GENES; i++){
        //Se toma el gen del padre y madre
        unsigned char fatherGene = fatherGeneticInformation->getGene(i);
        unsigned char motherGene = motherGeneticInformation->getGene(i);
        unsigned char tmpMask = (unsigned char)(rand()%256);
        //Se aplican y asignan las mascaras
        *(newGeneticMaterialOne + i) = (tmpMask & fatherGene)|(~tmpMask & motherGene);
        *(newGeneticMaterialTwo + i) = (~tmpMask & fatherGene)|(tmpMask & motherGene);
    }
    Chromosome* optionOne = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(optionOne) Chromosome(newGeneticMaterialOne);

    Chromosome* optionTwo = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(optionTwo) Chromosome(newGeneticMaterialTwo);

    if(GeneralFitnessCalculator::getInstance()->calculateFitness(optionOne)
       >= GeneralFitnessCalculator::getInstance()->calculateFitness(optionTwo)){
        free(optionTwo);
        return optionOne;
    }else{
        free(optionOne);
        return optionTwo;
    }
}