//
// Created by roberto on 01/05/15.
//

#include "lifeLaboratory.h"

Chromosome* selectChromosome(Chromosome* firstSon,Chromosome* secondSon){

};

Subject* selectParents(Tree* population){
    
};

Subject* createGeneration(Tree* population, int numberOfNewSubjects, int generationNumber){
    //Reserva espacio para N sujetos segun parametro
    Subject* newGeneration = static_cast<Subject*> (malloc(sizeof(Subject)*numberOfNewSubjects));
    //Llena la nueva generacion
    for (int i = 0; i < numberOfNewSubjects; ++i) {
        //Busca padres
        Subject* parents = selectParents(population);
        //Reserva espacio para los cromosomas resultantes
        Chromosome* optionsToReproduce = static_cast<Chromosome*>(malloc(2*sizeof(Chromosome)));
        //Mezcla cromosomas
        ChromosomeMixer::mix(parents->getGeneticInformation(), 
                             (parents+sizeof(Subject))->getGeneticInformation(),
                             optionsToReproduce);
        //Evalua cromosomas
        Chromosome* luckyChromosome = selectChromosome(optionsToReproduce,optionsToReproduce+sizeof(Chromosome));
        //Crea el nuevo sujeto
        new(newGeneration+i*sizeof(Subject)) Subject(parents, parents+sizeof(Subject),luckyChromosome, generationNumber);
    }
    //Retorna el puntero a la nueva generacion
    return newGeneration;
};