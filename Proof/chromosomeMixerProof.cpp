//
// Created by roberto on 27/04/15.
//

#include "chromosomeMixerProof.h"

void printChromosome(Chromosome* toPrint){
    for(int i =0; i < toPrint->getNumberOfGenes(); i++){
        for(int j = 0; j < GENE_LEN_ON_BYTES; j++){
            BinaryReader::read(toPrint->getGene(i),GENE_LEN_ON_BYTES,BinaryReader::printBinary,0);
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
    ChromosomeMixer* mixer = ChromosomeMixer::getInstance();
    Chromosome chromosomeMix = mixer->mix(father,mother);
    printChromosome(&chromosomeMix);
};