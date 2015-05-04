//
// Created by pablo on 03/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_SOCKETLOGIC_H
#define PROJECTMIDGARDLOGIC_SOCKETLOGIC_H

static const int PORT = 53000;

#include <SFML/Network.hpp>
#include "../libs/rapidjson/writer.h"
#include "../libs/rapidjson/stringbuffer.h"
#include <iostream>
using namespace sf;
using namespace rapidjson;
class SocketLogic {
    SocketLogic();
    static SocketLogic *singleton;
    TcpListener listener;
    TcpSocket client;
    void init();
    static bool initialized;
public:
    static SocketLogic* getInstance();
    void updateSubject(unsigned int idSubject, unsigned int x, unsigned int y);
    void createSubject(unsigned int idSubject, unsigned int x, unsigned int y,
                       unsigned int r, unsigned int g, unsigned int b);
    void changeEdda(std::string edda);
    void battleDetails(unsigned int idBattle, char* somedata);//TODO-roberto definir info de peleas


};


#endif //PROJECTMIDGARDLOGIC_SOCKETLOGIC_H
