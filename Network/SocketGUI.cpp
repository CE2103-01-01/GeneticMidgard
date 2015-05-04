//
// Created by pablo on 03/05/15.
//


#include "SocketGUI.h"
bool SocketGUI::initialized = false;
SocketGUI* SocketGUI::singleton = NULL;


SocketGUI::SocketGUI() {
   if (!initialized) init();
}

SocketGUI *SocketGUI::getInstance() {
    if (!singleton) singleton = new SocketGUI();
    return singleton;
}



void SocketGUI::init() {
    initialized = true;
    std::cout<< "Waiting connection..."<<std:: endl;
    while (true) {
        Socket::Status status = socket.connect(IP_ADDRESS, PORT);
        if (status != sf::Socket::Done) {
            sleep(seconds(RECONNECT_TIME));
        }
        else {
            std::cout<<"Connected"<<std::endl;
            break;
        }

    }
}
