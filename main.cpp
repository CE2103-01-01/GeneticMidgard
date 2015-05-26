#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"
#include "Models/AgeManager.h"
#include "Data/FileManager.h"

int main()
{
    Terrain::initArray();
    trueRandom::init();

    Thread socketThread(&SocketLogic::getInstance);
    socketThread.launch();

    AgeManager* manager = static_cast<AgeManager*>(malloc(sizeof(AgeManager)));
    new(manager) AgeManager();

    return 0;
}