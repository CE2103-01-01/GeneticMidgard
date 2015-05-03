//
// Created by pablo on 22/04/15.
//


#include "Chromosome.h"

using namespace constantsSubjectXML;

/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 */
Chromosome::Chromosome() {
    numberOfGenes = static_cast<int*>(malloc(sizeof(int)));
    *numberOfGenes = NUMBER_OF_GENES;
    trueRandom::init();
    geneticData = static_cast<unsigned char*>(malloc((*numberOfGenes) * GENE_LEN_ON_BYTES));
    for (int i = 0; i < (*numberOfGenes)*(GENE_LEN_ON_BYTES); i+=GENE_LEN_ON_BYTES) {
        for(int j = 0; j < GENE_LEN_ON_BYTES; j++){
            *static_cast<unsigned char*>(geneticData + i + j) = trueRandom::getRandom()%256;
        }
    }
};

/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 */
Chromosome::Chromosome(unsigned char* genes) {
    numberOfGenes = static_cast<int*>(malloc(sizeof(int)));
    *numberOfGenes = NUMBER_OF_GENES;
    geneticData = genes;
};

/**Buscador de gen
 * @brief Realiza aritmetica de punteros con el numero  y tamaño del gen
 * @param int geneNumber: numero de gen
 * @return void*: espacio de memoria que ocupa el gen
 */
unsigned char* Chromosome::getGene(int geneNumber) {
    if(geneNumber < *numberOfGenes){
        return geneticData + geneNumber*GENE_LEN_ON_BYTES;
    }else{
        return 0;
    }
}

/**Accede al numero de genes
 * @return int: *numberOfGenes
 */
int Chromosome::getNumberOfGenes(){
    return *numberOfGenes;
};