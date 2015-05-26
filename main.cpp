#include "Models/Population.h"
#include "Network/SocketLogic.h"
#include "Models/Terrain.h"
#include "Models/AgeManager.h"
#include "Data/FileManager.h"

int main()
{
    const char* newText = "some text";
    int size = 9;
    int id = 1;
    FileManager::writeFile(newText, id, size);

    char* readedText = static_cast<char*>(malloc(size));
    FileManager::readFile(readedText, id, size);

    for(int i = 0; i < size; i++){
        std::cout << *(readedText + i) << std::endl;
    }

    Terrain::initArray();
    trueRandom::init();

    Thread socketThread(&SocketLogic::getInstance);
    socketThread.launch();

    AgeManager* manager = static_cast<AgeManager*>(malloc(sizeof(AgeManager)));
    new(manager) AgeManager();

    return 0;
}