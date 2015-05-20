#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"
#include "Models/AgeManager.h"

int main()
{
    Terrain::initArray();
    trueRandom::init();

    //SocketLogic::getInstance();

    AgeManager manager = AgeManager();

    return 0;
}