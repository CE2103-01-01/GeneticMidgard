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
    unsigned char* newGeneticMaterial = static_cast<unsigned char*>(malloc(2*numOfGenes));
    for(int i=0; i < numOfGenes; i++){
        //Se toma el gen del padre, la madre y los hijos
        unsigned char* fatherGene = fatherGeneticInformation->getGene(i);
        unsigned char* motherGene = motherGeneticInformation->getGene(i);
        unsigned char* firstSonGene = newGeneticMaterial + i;
        unsigned char* secondSonGene = newGeneticMaterial + numOfGenes + i;
            //Se crea mascara y el pedazo de gen temporal
        unsigned char tmpMask = (unsigned char)(rand()%256);
        //Se aplican y asignan las mascaras
        *(firstSonGene) = (tmpMask & *(fatherGene))|(~tmpMask & *(motherGene));
        *(secondSonGene) = (~tmpMask & *(fatherGene))|(tmpMask & *(motherGene));
    }
    new(toReturn) Chromosome(newGeneticMaterial);
    new(toReturn+sizeof(Chromosome)) Chromosome(newGeneticMaterial + numOfGenes);
    free(newGeneticMaterial);
    return toReturn;
};