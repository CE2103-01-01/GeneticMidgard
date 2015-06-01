//
// Created by pablo on 03/05/15.
//

#include <signal.h>
#include "SocketLogic.h"

SocketLogic* SocketLogic::singleton = NULL;
bool SocketLogic::initialized  = false;
void SocketLogic::init() {
    signal(SIGTERM,&exit);
    initialized = true;
    if(!NETWORK_ACTIVATED) return;
    on = true;
    if (listener.listen(PORT) != sf::Socket::Done)
    {
        std::cerr<<"Error on create listener"<<std::endl;
        return;
    }

    else if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr<<"Error on create client"<<std::endl;
        return;
    }
    else {
        std::cout << "Connected!" << std::endl;
        Packet packet;
        packet<<"{\"action\":\"hello\"}";
        send.lock();
        client.send(packet);
        send.unlock();
    }

    Packet packet;
    std::string message;
    client.receive(packet);
    packet>>message;
    if(message == "{\"action\":\"hello\"}") std::cout << "Connection Tested" << std::endl;

    //receiving();
}
SocketLogic *SocketLogic::getInstance() {
    if(!singleton) singleton = new SocketLogic();
    return singleton;
}

SocketLogic::SocketLogic() {
    if(!initialized) init();
}
void SocketLogic::updateObject(unsigned int idSubject, unsigned int x, unsigned int y){
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("updateObject");
    writer.String("id"); writer.Uint(idSubject);
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    client.send(packet);
    send.unlock();
}

void SocketLogic::updateSubject(unsigned int idSubject, unsigned int x, unsigned int y) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("updateSubject");
    writer.String("id"); writer.Uint(idSubject);
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    client.send(packet);
    send.unlock();
}

void SocketLogic::createSubject(unsigned int idSubject, unsigned int x, unsigned int y, unsigned int r, unsigned int g,
                                unsigned int b) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("createSubject");
    writer.String("id"); writer.Uint(idSubject);
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.String("r"); writer.Uint(r);
    writer.String("g"); writer.Uint(g);
    writer.String("b"); writer.Uint(b);
    writer.EndObject();
    std::string tmp = s.GetString();
    packet<<tmp;
    send.lock();
    client.send(packet);
    send.unlock();
}
void SocketLogic::lifeUpdate(unsigned int idSubject, int lifeUpdate) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("lifeUpdate");
    writer.String("id"); writer.Uint(idSubject);
    writer.String("size"); writer.Int(lifeUpdate);
    writer.EndObject();
    std::string tmp = s.GetString();
    packet<<tmp;
    send.lock();
    client.send(packet);
    send.unlock();
}
void SocketLogic::changeEdda(std::string edda) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("changeEdda");
    writer.String("id"); writer.String(edda.c_str());
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    client.send(packet);
    send.unlock();
}

void SocketLogic::createObject(unsigned int idObject,  unsigned int x, unsigned int y) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("createObject");
    writer.String("id"); writer.Uint(idObject);
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.EndObject();
    std::string tmp = s.GetString();
    packet<<tmp;
    send.lock();
    client.send(packet);
    send.unlock();
}

void SocketLogic::deleteObject(unsigned int idObject) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action");
    writer.String("deleteObject");
    writer.String("id");
    writer.Uint(idObject);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    client.send(packet);
    send.unlock();
}
void SocketLogic::deleteSubject(unsigned int idObject) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action");
    writer.String("deleteSubject");
    writer.String("id");
    writer.Uint(idObject);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    client.send(packet);
    send.unlock();
}

void SocketLogic::receiving() {
    while (on) {

        Packet packet;
        std::string message;
        if (client.receive(packet) != sf::Socket::Done) {
            break;
        }
        packet>>message;
        std::cout << "Received: " << message<< std::endl;
        manageMessage(message);
    }
}

SocketLogic::~SocketLogic() {
    on = false;
    client.disconnect();
    free(singleton);
}

void createSubject(unsigned int idSubject, unsigned int x, unsigned int y, unsigned int r, unsigned int g,
                   unsigned int b) {
    SocketLogic::getInstance()->createSubject(idSubject,x,y,r,g,b);
}

void deleteSubject(unsigned int idSubject) {
    SocketLogic::getInstance()->deleteSubject(idSubject);
}

void updateSubject(unsigned int idSubject, unsigned int x, unsigned int y){
    SocketLogic::getInstance()->updateSubject(idSubject, x, y);
}

void updateObject(unsigned int idObject, unsigned int x, unsigned int y){
    SocketLogic::getInstance()->updateObject(idObject,x,y);

}

void lifeUpdate(unsigned int idSubject, int lifeUpdate) {
    SocketLogic::getInstance()->lifeUpdate(idSubject, lifeUpdate);
}

void deleteObject(unsigned int id){
    SocketLogic::getInstance()->deleteObject(id);
}

void createObject(unsigned int idObject, unsigned int x, unsigned int y) {
    SocketLogic::getInstance()->createObject(idObject,x,y);
}

void changeEdda(std::string edda) {
    SocketLogic::getInstance()->changeEdda(edda);
}

void SocketLogic::manageMessage(std::string string) {

}


void exit() {
    SocketLogic::getInstance()->~SocketLogic();
}

void SocketLogic::createGod(unsigned int idGod, unsigned int x, unsigned int y, unsigned int r, unsigned int g,
                            unsigned int b) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("createGod");
    writer.String("id"); writer.Uint(idGod);
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.String("r"); writer.Uint(r);
    writer.String("g"); writer.Uint(g);
    writer.String("b"); writer.Uint(b);
    writer.EndObject();
    std::string tmp = s.GetString();
    packet<<tmp;
    send.lock();
    client.send(packet);
    send.unlock();
}

void SocketLogic::updateGod(unsigned int idGod, unsigned int x, unsigned int y) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("updateGod");
    writer.String("id"); writer.Uint(idGod);
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    client.send(packet);
    send.unlock();
}

void SocketLogic::deleteGod(unsigned int id) {
    if(!NETWORK_ACTIVATED) return;
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action");
    writer.String("deleteGod");
    writer.String("id");
    writer.Uint(id);
    writer.EndObject();
    packet<<s.GetString();
    send.lock();
    client.send(packet);
    send.unlock();
}
