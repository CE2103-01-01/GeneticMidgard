
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

    Chromosome* chromosomeProof = static_cast<Chromosome*>(malloc(sizeof(Chromosome)));\
    new(chromosomeProof) Chromosome();
    std::cout << chromosomeProof->getNumberOfGenes() << std::endl;

    GeneralFitnessCalculator* calculatorProof = static_cast<GeneralFitnessCalculator*>(malloc(sizeof(GeneralFitnessCalculator)));
    new(calculatorProof) GeneralFitnessCalculator();
    std::cout << calculatorProof->calculateFitness(chromosomeProof) << std::endl;
    return 0;


}