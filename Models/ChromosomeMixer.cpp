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
    int numOfGenes = fatherGeneticInformation->getNumberOfGenes();
    void* newGeneticMaterial = malloc(2*numberOfGenes*GENE_LEN_ON_BYTES);
    for(int i=0; i < numOfGenes; i++){
        //Se toma el gen del padre, la madre y los hijos
        unsigned char* fatherGene =
                static_cast<unsigned char*>(fatherGeneticInformation->getGene(i));
        unsigned char* motherGene =
                static_cast<unsigned char*>(motherGeneticInformation->getGene(i));
        unsigned char* firstSonGene =
                static_cast<unsigned char*>(newGeneticMaterial + i*GENE_LEN_ON_BYTES);
        unsigned char* secondSonGene =
                static_cast<unsigned char*>(newGeneticMaterial + (i+numOfGenes-1)*GENE_LEN_ON_BYTES);
        //Se recorre el gen byte por byte
        for(int j=0; j < GENE_LEN_ON_BYTES; j++){
            //Se crea mascara y el pedazo de gen temporal
            unsigned char tmpMask = (unsigned char)(rand()%256);
            //Se aplican y asignan las mascaras
            *(firstSonGene+j) = (tmpMask & *(fatherGene + j))|(~tmpMask & *(motherGene + j));
            *(secondSonGene+j) = (~tmpMask & *(fatherGene + j))|(tmpMask & *(motherGene + j));
        }
    }
    Chromosome* toReturn = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));
    new(toReturn) Chromosome(newGeneticMaterial);
    new(toReturn+sizeof(Chromosome)) Chromosome(newGeneticMaterial + numOfGenes*GENE_LEN_ON_BYTES);
    return toReturn;
};