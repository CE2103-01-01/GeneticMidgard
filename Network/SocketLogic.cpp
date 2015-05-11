//
// Created by pablo on 03/05/15.
//

#include "SocketLogic.h"
bool SocketLogic::initialized  = false;
void SocketLogic::init() {
    initialized = true;
    if (listener.listen(PORT) != sf::Socket::Done)
    {
        std::cout<<"Error on create listener"<<std::endl;
    }

    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout<<"Error on create client"<<std::endl;
    }
}
SocketLogic* SocketLogic::singleton = NULL;
SocketLogic *SocketLogic::getInstance() {
    if(!singleton) singleton = new SocketLogic();
    return singleton;
}

SocketLogic::SocketLogic() {
    if(!initialized) init();
}

void SocketLogic::updateSubject(unsigned int idSubject, unsigned int x, unsigned int y) {
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
    client.send(packet);
}

void SocketLogic::createSubject(unsigned int idSubject, unsigned int x, unsigned int y, unsigned int r, unsigned int g,
                                unsigned int b) {
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
    client.send(packet);
}

void SocketLogic::changeEdda(std::string edda) {
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("changeEdda");
    writer.String("id"); writer.String(edda.c_str());
    writer.EndObject();
    packet<<s.GetString();
    client.send(packet);
}

void SocketLogic::createObject(unsigned int idObject, std::string type, unsigned int x, unsigned int y) {
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("createObject");
    writer.String("id"); writer.Uint(idObject);
    writer.String("type"); writer.String(type.c_str());
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.EndObject();
    packet<<s.GetString();
    client.send(packet);
}

void SocketLogic::deleteObject(unsigned int idObject) {
    if(!initialized) return;
    Packet packet;
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("deleteObject");
    writer.String("id"); writer.Uint(idObject);
    writer.EndObject();
    packet<<s.GetString();
    client.send(packet);
}
