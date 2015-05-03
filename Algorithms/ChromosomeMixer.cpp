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
Chromosome* ChromosomeMixer::mix(Chromosome* fatherGeneticInformation,
                                 Chromosome* motherGeneticInformation,
                                 Chromosome* toReturn)
{
    int numOfGenes = fatherGeneticInformation->getNumberOfGenes();
    void* newGeneticMaterial = malloc(2*numOfGenes);
    for(int i=0; i < numOfGenes; i++){
        //Se toma el gen del padre, la madre y los hijos
        unsigned char* fatherGene =
                static_cast<unsigned char*>(fatherGeneticInformation->getGene(i));
        unsigned char* motherGene =
                static_cast<unsigned char*>(motherGeneticInformation->getGene(i));
        unsigned char* firstSonGene =
                static_cast<unsigned char*>(newGeneticMaterial + i);
        unsigned char* secondSonGene =
                static_cast<unsigned char*>(newGeneticMaterial + numOfGenes + i);
            //Se crea mascara y el pedazo de gen temporal
        unsigned char tmpMask = (unsigned char)(rand()%256);
        //Se aplican y asignan las mascaras
        *(firstSonGene) = (tmpMask & *(fatherGene))|(~tmpMask & *(motherGene));
        *(secondSonGene) = (~tmpMask & *(fatherGene))|(tmpMask & *(motherGene));
    }
    *(toReturn) = Chromosome(newGeneticMaterial);
    *(toReturn+sizeof(Chromosome)) = Chromosome(newGeneticMaterial + numOfGenes);
    return toReturn;
};