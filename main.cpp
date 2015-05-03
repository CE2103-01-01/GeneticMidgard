#include "Proof/laboratoryProof.h"

#include "../GeneticMidgard/Data/BitVector.h"
#include "iostream"
#include "Models/Chromosome.h"
#include "Algorithms/GeneralFitnessCalculator.h"
#include "Models/Terrain.h"

int main()
{
    Terrain::initArray();
    Terrain::printArray();
    DoubleList<Vector2D> a = Terrain::findPathAS(Vector2D(0,0), Vector2D(5,5));
    laboratoryProof();
    return 0;


}