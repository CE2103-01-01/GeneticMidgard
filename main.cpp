#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"

int main()
{
    Terrain::initArray();
   // SocketLogic::getInstance();

    Population* population = static_cast<Population*>(malloc(sizeof(Population)));
    new(population) Population(0);

    population->init_pthread();
    pthread_join(*population->get_pthread(),0);
    return 0;
}