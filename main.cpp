#include "Network/SocketLogic.h"
#include "Models/AgeManager.h"
#include <SFML/Audio.hpp>

void bigBang(){
    //sf::SoundBuffer fileBuffer;
    //if (fileBuffer.loadFromFile("res/francafrique.wav")){
    //    sf::Sound sound;
    //    sound.setBuffer(fileBuffer);
    //    sound.play();
        if(NETWORK_ACTIVATED)SocketLogic::getInstance();
        Terrain::initArray();
        trueRandom::init();
        AgeManager* manager = static_cast<AgeManager*>(malloc(sizeof(AgeManager)));
        new(manager) AgeManager();
    //}
}

int main() {
    bigBang();
    return 0;
}