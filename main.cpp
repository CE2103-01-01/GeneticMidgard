
#include "../GeneticMidgard/Data/BitVector.h"
#include "iostream"

int main()
{

    BitVector* b = new BitVector(sizeof(int));

    b->set(5);
    b->set(6);

    std::cout << b->get(5) << std::endl;

    return 0;


}