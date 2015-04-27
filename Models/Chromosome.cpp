//
// Created by pablo on 22/04/15.
//


#include "Chromosome.h"

using namespace pugi;

/**Constructor
 * @brief Crea la cantidad de genes del archivo genes.xml con tamaño definido en Constants.h
 */
Chromosome::Chromosome() {
    xml_document genesXML;
    genesXML.load_file(GENES_XML_PATH);
    numberOfGenes = static_cast<int*>(malloc(sizeof(int)));
    *numberOfGenes = genesXML.child(GENES_XML_ROOT).child(GENES_XML_LENGHT).attribute(GENES_XML_LENGHT_INFO).as_int();
    geneticData = malloc((*numberOfGenes) * GENE_LEN_ON_BYTES);
    srand(time(NULL));
    for (int i = 0; i < *numberOfGenes; ++i) {
        for(int j = 0; j < GENE_LEN_ON_BYTES; j++){
            *static_cast<char*>(geneticData + i*j) = rand()%256;
        }
    }
};

/**Buscador de gen
 * @brief Realiza aritmetica de punteros con el numero  y tamaño del gen
 * @param int geneNumber: numero de gen
 * @return void*: espacio de memoria que ocupa el gen
 */
void* Chromosome::getGene(int geneNumber) {
  return geneticData + geneNumber*GENE_LEN_ON_BYTES;
}