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

};