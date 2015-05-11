#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"
#include "Models/PopulationManager.h"

int main()
{
    Terrain::initArray();
    SocketLogic::getInstance();

    pthread_mutex_t* mutex;
    pthread_mutex_init(mutex,NULL);
    PopulationManager* populationManager = PopulationManager::getInstance(mutex);
    populationManager->killEmAll();

    return 0;
}