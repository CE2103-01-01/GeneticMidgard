#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"
#include "Models/PopulationManager.h"

int main()
{
   // Terrain::initArray();
   // SocketLogic::getInstance();

    pthread_mutex_t* mutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(mutex,NULL);
    PopulationManager* populationManager = PopulationManager::getInstance(mutex);
    pthread_join(*populationManager->get_pthread(),0);
    return 0;
}