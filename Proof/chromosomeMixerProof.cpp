//
// Created by roberto on 27/04/15.
//

#include "chromosomeMixerProof.h"

void printChromosome(Chromosome* toPrint){
    for(int i =0; i < toPrint->getNumberOfGenes(); i++){
        for(int j = 0; j < GENE_LEN_ON_BYTES; j++){
            printBinary(*(static_cast<unsigned char*>(toPrint->getGene(i)) + j));
        }
    }
    std::cout << std::endl;
};

void chromosomeMixerProof(){
    Chromosome* father = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(father) Chromosome();
    printChromosome(father);
    Chromosome* mother = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(mother) Chromosome();
    printChromosome(mother);
    Chromosome* chromosomeMix = static_cast<Chromosome*>(malloc(2*sizeof(Chromosome)));
    ChromosomeMixer::mix(father,mother,chromosomeMix);
    printChromosome(chromosomeMix);
    printChromosome(chromosomeMix+sizeof(Chromosome));
};