//
// Created by pablo on 03/05/15.
//


#include <signal.h>
#include "SocketGUI.h"
#include "../GUI/Objects.h"


int SocketGUI::popul = 0;
bool SocketGUI::initialized = false;
SocketGUI* SocketGUI::singleton = NULL;


SocketGUI::SocketGUI() {
   if (!initialized) init();
}
SocketGUI::~SocketGUI() {
    on = false;
    socket.disconnect();
}
SocketGUI *SocketGUI::getInstance() {
    if (!singleton) singleton = new SocketGUI();
    return singleton;
}



void SocketGUI::init() {
    signal(SIGTERM,&exit);
    if(!NETWORK_ACTIVATED) return;
    on = true;
    initialized = true;
    std::cout<< "Waiting connection..."<<std:: endl;
    while (true) {
        Socket::Status status = socket.connect(IP_ADDRESS, PORT);
        if (status != sf::Socket::Done) {
            sleep(seconds(RECONNECT_TIME));
        }
        else {
            std::cout<<"Connected"<<std::endl;
            Packet packet;
            packet<<"{\"action\":\"hello\"}";
            send.lock();
            socket.send(packet);
            send.unlock();
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
        popul+=1;
        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        unsigned int r = document.FindMember("r")->value.GetUint();
        unsigned int g = document.FindMember("g")->value.GetUint();
        unsigned int b = document.FindMember("b")->value.GetUint();
        Person person(id,x,y,r,g,b);
        Map::getInstance()->getPoblacion()->addPerson(person);
    }
     else if (action == "createGod")
    {
        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        unsigned int r = document.FindMember("r")->value.GetUint();
        unsigned int g = document.FindMember("g")->value.GetUint();
        unsigned int b = document.FindMember("b")->value.GetUint();
        Person god(id,x,y,r,g,b);
        Map::getInstance()->getGods()->addPerson(god);
    }
    else if (action == "createObject")
    {
        //ID = numeroDeObjeto*10000 + 8888... Ej: 18888,28888,38888,...
        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        //TODO: TERMINIAR
    }
    else if (action == "updateSubject")
    {

        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        Map::getInstance()->getPoblacion()->updateId(id,x,y);
    }
    else if (action == "updateGods")
    {

        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        Map::getInstance()->getGods()->updateId(id,x,y);
    }
    else if (action == "lifeUpdate")
    {
        //std::cout << "Life Update" << std::endl;
        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int size = document.FindMember("size")->value.GetInt();
        Map::getInstance()->getPoblacion()->updateLifeId(id,size);
    }
    else if (action == "deleteSubject")
    {
        popul-=1;
        std::cout << "Population: " << popul << std::endl;
        unsigned int id = document.FindMember("id")->value.GetUint();
        Map::getInstance()->getPoblacion()->deletePerson(id);
    }
    else if (action == "deleteGod")
    {
        unsigned int id = document.FindMember("id")->value.GetUint();
        Map::getInstance()->getGods()->deletePerson(id);
    }
    else if (action == "createObject")
    {
        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        Object object(id,x,y);
        Map::getInstance()->getObjects()->addObject(object);
    }
    else if (action == "updateObject")
    {

        unsigned int id = document.FindMember("id")->value.GetUint();
        unsigned int x = document.FindMember("x")->value.GetUint();
        unsigned int y = document.FindMember("y")->value.GetUint();
        Map::getInstance()->getObjects()->updateId(id,x,y);
    }

    else if (action == "deleteObject")
    {
        unsigned int id = document.FindMember("id")->value.GetUint();
        Map::getInstance()->getObjects()->deleteObject(id);
    }

    (Map::getInstance()->needToPaint) = true;

}

void SocketGUI::updateSpeed(unsigned char speed) {
    if(!NETWORK_ACTIVATED) return;
    if (!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("updateSpeed");
    writer.String("speed"); writer.Uint(speed);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    socket.send(packet);
    send.unlock();
    std::cout << "sent" << std::endl;
}



void SocketGUI::detailsSubject(unsigned int id) {
    if(!NETWORK_ACTIVATED) return;
    if (!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("detailsSubject");
    writer.String("id"); writer.Uint(id);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    socket.send(packet);
    send.unlock();
}

void exit() {
    SocketGUI::getInstance()->~SocketGUI();
}
