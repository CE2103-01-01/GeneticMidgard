//
// Created by pablo on 03/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_SOCKETLOGIC_H
#define PROJECTMIDGARDLOGIC_SOCKETLOGIC_H


#include "SocketConfig.h"
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
    Mutex send;
public:
    static SocketLogic* getInstance();
    void updateSubject(unsigned int, unsigned int, unsigned int);
    void createSubject(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
    void createObject(unsigned int, std::string, unsigned int, unsigned int);
    void deleteObject(unsigned int);
    void changeEdda(std::string);
    void battleDetails(unsigned int, char*);//TODO-roberto definir info de peleas


};

void createSubject(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
void deleteSubject(unsigned int idSubject);

#endif //PROJECTMIDGARDLOGIC_SOCKETLOGIC_H
