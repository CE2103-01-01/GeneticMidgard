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
    receiving();
}

void SocketGUI::receiving() {
    while (true) {
        Packet packet;
        std::string message;
        if (socket.receive(packet) != sf::Socket::Done) {
            break;
        }
        packet>>message;
        std::cout << "Received: " << message<< std::endl;
        Thread thread(std::bind(&SocketGUI::manageMessage, message));
        thread.launch();
    }
}

void SocketGUI::manageMessage(std::string string) {
    rapidjson::Document document;
    document.Parse(string.c_str());
    std::string action = document.FindMember("action")->value.GetString();
    if (action == "createSubject")
    {
        std::cout << "createSubject: " << std::endl;
    }
    else if (action == "updateSubject")
    {
        std::cout << "updateSubject: " << std::endl;
    }
    else if (action == "changeEdda")
    {
        std::cout << "changeEdda: " << std::endl;
    }


}
