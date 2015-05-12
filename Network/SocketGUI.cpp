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
        needToPaint = true;
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
        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        unsigned int r = document.FindMember("r")->value.GetUint();
        unsigned int g = document.FindMember("g")->value.GetUint();
        unsigned int b = document.FindMember("b")->value.GetUint();
        Person person(id,x,y,r,g,b);
        Map::getInstance()->getPoblacion()->addPerson(person);
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

void SocketGUI::updateSpeed(unsigned char speed) {
    if (!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("updateSpeed");
    writer.String("speed"); writer.Uint(speed);
    writer.EndObject();
    packet<<s.GetString();
    socket.send(packet);
}
