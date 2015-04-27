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
    Chromosome* toReturn = static_cast<Chromosome*>(malloc(2*sizeof(Chromosome)));
    for(int i=0; i < (fatherGeneticInformation->getNumberOfGenes()*GENE_LEN_ON_BYTES); i+=GENE_LEN_ON_BYTES){
        for(int j=0; j < GENE_LEN_ON_BYTES; j++){
            //Se crea mascara temporal
            unsigned char tmpMask = static_cast<unsigned char>(rand()%256);
            //Se toma el gen del padre y de la madre
            unsigned char* fatherGene = *static_cast<unsigned char*>(fatherGeneticInformation + i + j);
            unsigned char* motherGene = *static_cast<unsigned char*>(motherGeneticInformation + i + j);
            //Se toma el gen respectivo de los hijos
            unsigned char* firstSonGene = static_cast<unsigned char*>(toReturn + i + j);
            unsigned char* secondSonGene = static_cast<unsigned char*>(toReturn + sizeof(Chromosome) + i + j);
            //Se aplica la mascara para generar dos hijos
            *firstSonGene = (tmpMask & fatherGene)|(~tmpMask & motherGene);
            *secondSonGene = (~tmpMask & fatherGene)|(tmpMask & motherGene);
        }
    }
    return toReturn;
};