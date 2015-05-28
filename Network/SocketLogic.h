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
    bool on;
    Mutex send;
public:
    ~SocketLogic();
    static SocketLogic* getInstance();
    void receiving();
    void createSubject(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
    void updateSubject(unsigned int, unsigned int, unsigned int);
    void deleteSubject(unsigned int);
    void lifeUpdate(unsigned int, int);
    void createObject(unsigned int, unsigned int, unsigned int);
    void deleteObject(unsigned int);
    void changeEdda(std::string);
    void manageMessage(std::string);


};

void createObject(unsigned int, unsigned int, unsigned int);
void deleteObject(unsigned int);
void createSubject(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
void deleteSubject(unsigned int idSubject);
void updateSubject(unsigned int, unsigned int, unsigned int);
void lifeUpdate(unsigned int, int);
void changeEdda(std::string);
void battleDetails(unsigned int, char*);
void exit();

#endif //PROJECTMIDGARDLOGIC_SOCKETLOGIC_H
