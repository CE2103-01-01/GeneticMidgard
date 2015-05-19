#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"
#include "Models/PopulationManager.h"

int main()
{
    Terrain::initArray();

    SocketLogic::getInstance();


    return 0;
}