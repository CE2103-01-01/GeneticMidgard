//
// Created by pablo on 22/04/15.
//


#include "Chromosome.h"

using namespace pugi;
using namespace constantsSubjectXML;

/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 */
Chromosome::Chromosome() {
    numberOfGenes = static_cast<int*>(malloc(sizeof(int)));
    *numberOfGenes = readLenghtFromXML();
    trueRandom::init();
    geneticData = malloc((*numberOfGenes) * GENE_LEN_ON_BYTES);
    for (int i = 0; i < (*numberOfGenes)*(GENE_LEN_ON_BYTES); i+=GENE_LEN_ON_BYTES) {
        for(int j = 0; j < GENE_LEN_ON_BYTES; j++){
            *static_cast<unsigned char*>(geneticData + i + j) = trueRandom::getRandom()%256;
        }
    }
};

/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 */
Chromosome::Chromosome(void* genes) {
    numberOfGenes = static_cast<int*>(malloc(sizeof(int)));
    *numberOfGenes = readLenghtFromXML();
    geneticData = genes;
};

int Chromosome::readLenghtFromXML(){
    xml_document genesXML;
    genesXML.load_file(GENES_XML_PATH);
    return genesXML.child(GENES_XML_ROOT).child(GENES_XML_LENGHT).attribute(GENES_XML_LENGHT_INFO).as_int();
};

/**Buscador de gen
 * @brief Realiza aritmetica de punteros con el numero  y tamaño del gen
 * @param int geneNumber: numero de gen
 * @return void*: espacio de memoria que ocupa el gen
 */
void* Chromosome::getGene(int geneNumber) {
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