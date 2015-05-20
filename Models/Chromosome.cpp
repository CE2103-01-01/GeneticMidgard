//
// Created by pablo on 22/04/15.
//


#include "Chromosome.h"

using namespace constantsSubjectXML;

/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 */
Chromosome::Chromosome() {
    geneticData = static_cast<unsigned char*>(malloc(sizeof(unsigned char)*NUMBER_OF_GENES));
    for (int i = 0; i < NUMBER_OF_GENES; i++) {
        *(geneticData+i) = trueRandom::getRandom()%256;
    }
}


/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 * @param unsigned char genes[]: genes
 */
Chromosome::Chromosome(unsigned char* genes) {
    geneticData = static_cast<unsigned char*>(malloc(sizeof(unsigned char)*NUMBER_OF_GENES));
    for (int i = 0; i < NUMBER_OF_GENES; i++) {
        *(geneticData+i) = *(genes+i);
    }
}

/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 * @param const Chromosome& other: cromosoma a copiar
 */
Chromosome::Chromosome(const Chromosome& other) {
    geneticData = static_cast<unsigned char*>(malloc(sizeof(unsigned char)*NUMBER_OF_GENES));
    for (int i = 0; i < NUMBER_OF_GENES; i++) {
        *(geneticData+i) = *(other.geneticData+i);
    }
}

/**Destructor
 */
Chromosome::~Chromosome(){
    free(geneticData);
}

/**Buscador de gen
 * @brief Realiza aritmetica de punteros con el numero  y tamaño del gen
 * @param int geneNumber: numero de gen
 * @return void*: espacio de memoria que ocupa el gen
 */
unsigned char Chromosome::getGene(int geneNumber) {
    if(geneNumber < NUMBER_OF_GENES){
        return geneticData[geneNumber];
    }else{
        return 0;
    }
}