
#include "../GeneticMidgard/Data/BitVector.h"
#include "iostream"
#include "Models/Chromosome.h"
#include "Algorithms/GeneralFitnessCalculator.h"

int main()
{
/*
        BitVector* b = new BitVector(sizeof(int));

        b->set(5);
        b->set(6);

        std::cout << b->get(5) << std::endl;
*/

    Chromosome* hola = new Chromosome();
    GeneralFitnessCalculator* hola2 = new GeneralFitnessCalculator();
    int valor =  *static_cast<unsigned char*>(hola->getGene(0));
    std::cout<<hola2->calculateFitness(hola)<<std::endl;
//
    return 0;


}