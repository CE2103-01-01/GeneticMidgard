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
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.String("action"); writer.String("updateSubject");
    writer.String("id"); writer.Uint(idSubject);
    writer.String("x"); writer.Uint(x);
    writer.String("y"); writer.Uint(y);
    writer.EndObject();
    client.send(s.GetString(),s.GetSize());
}

void SocketLogic::createSubject(unsigned int idSubject, unsigned int x, unsigned int y, unsigned int r, unsigned int g,
                                unsigned int b) {
    if(!initialized) return;
}

void SocketLogic::changeEdda(std::string edda) {
    if(!initialized) return;
}
