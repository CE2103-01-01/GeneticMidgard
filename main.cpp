#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"
#include "Models/AgeManager.h"
#include "Data/FileManager.h"

int main()
{

    if(NETWORK_ACTIVATED)
    {
        SocketLogic::getInstance();
    }
    Terrain::initArray();
    trueRandom::init();

    AgeManager* manager = static_cast<AgeManager*>(malloc(sizeof(AgeManager)));

    new(manager) AgeManager();



    return 0;
}