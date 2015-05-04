//
// Created by roberto on 27/04/15.
//

#include "ChromosomeMixer.h"

GeneralFitnessCalculator* ChromosomeMixer::calculator = 0;
ChromosomeMixer* ChromosomeMixer::instance = 0;

ChromosomeMixer::ChromosomeMixer(){}

/* Mezclador de cromosomas
 * @brief: Recibe la informacion genetica de dos individuos, la mezcla y retorna dos
 *         individuos que se accesan mediante aritmetica de punteros
 * @param: Chromosome* fatherGeneticInformation: cromosoma del padre
 * @param: Chromosome* motherGeneticInformation: cromosoma de la madre
 * @return Chromosome*: dos cromosomas hijos, (return) & (return + sizeof(Chromosome))
 */
Chromosome ChromosomeMixer::mix(Chromosome fatherGeneticInformation,
                          Chromosome motherGeneticInformation){
    //Mezcla cromosomas
    int numOfGenes = fatherGeneticInformation.getNumberOfGenes();
    unsigned char* newGeneticMaterialOne = static_cast<unsigned char*>(malloc(numOfGenes));
    unsigned char* newGeneticMaterialTwo = static_cast<unsigned char*>(malloc(numOfGenes));
    for(int i=0; i < numOfGenes; i++){
        //Se toma el gen del padre y madre
        unsigned char* fatherGene = fatherGeneticInformation.getGene(i);
        unsigned char* motherGene = motherGeneticInformation.getGene(i);
        unsigned char tmpMask = (unsigned char)(rand()%256);
        //Se aplican y asignan las mascaras
        *(newGeneticMaterialOne + i) = (tmpMask & *fatherGene)|(~tmpMask & *motherGene);
        *(newGeneticMaterialTwo + i) = (~tmpMask & *fatherGene)|(tmpMask & *motherGene);
    }

    Chromosome optionOne =  Chromosome(newGeneticMaterialOne);
    Chromosome optionTwo = Chromosome(newGeneticMaterialTwo);;

    if(calculator->calculateFitness(optionOne) >= calculator->calculateFitness(optionTwo)){
        return optionOne;
    }else{
        return optionTwo;
    }
};

ChromosomeMixer* ChromosomeMixer::getInstance(){
    if(!calculator){
        calculator = static_cast<GeneralFitnessCalculator*>(malloc(sizeof(GeneralFitnessCalculator)));
        *calculator = GeneralFitnessCalculator();
    }
    if(!instance){
        instance = static_cast<ChromosomeMixer*>(malloc(sizeof(ChromosomeMixer)));
        new(instance) ChromosomeMixer();
    }
    return instance;
};

GeneralFitnessCalculator *ChromosomeMixer::getCalculator() {
    return calculator;
}
