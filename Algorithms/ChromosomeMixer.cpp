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
Chromosome ChromosomeMixer::mix(Chromosome fatherGeneticInformation, Chromosome motherGeneticInformation){
    //Mezcla cromosomas
    unsigned char newGeneticMaterialOne[constantsSubjectXML::NUMBER_OF_GENES];
    newGeneticMaterialOne[constantsSubjectXML::NUMBER_OF_GENES] = {};
    unsigned char newGeneticMaterialTwo[constantsSubjectXML::NUMBER_OF_GENES];
    newGeneticMaterialTwo[constantsSubjectXML::NUMBER_OF_GENES] = {};
    for(int i=0; i < constantsSubjectXML::NUMBER_OF_GENES; i++){
        //Se toma el gen del padre y madre
        unsigned char fatherGene = fatherGeneticInformation.getGene(i);
        unsigned char motherGene = motherGeneticInformation.getGene(i);
        unsigned char tmpMask = (unsigned char)(rand()%256);
        //Se aplican y asignan las mascaras
        newGeneticMaterialOne[i] = (tmpMask & fatherGene)|(~tmpMask & motherGene);
        newGeneticMaterialTwo[i] = (~tmpMask & fatherGene)|(tmpMask & motherGene);
    }
    Chromosome optionOne =  Chromosome(newGeneticMaterialOne);
    Chromosome optionTwo = Chromosome(newGeneticMaterialTwo);

    float fitnessOne = GeneralFitnessCalculator::getInstance()->calculateFitness(&optionOne);
    float fitnessTwo = GeneralFitnessCalculator::getInstance()->calculateFitness(&optionTwo);

    if(fitnessOne >= fitnessTwo){
        return optionOne;
    }else{
        return optionTwo;
    }
}