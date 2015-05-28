//
// Created by pablo on 03/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_SOCKET_H
#define PROJECTMIDGARDLOGIC_SOCKET_H
#include "SocketConfig.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/writer.h"
#include "../GUI/Poblacion.h"
#include "../GUI/Map.h"
#include <iostream>
#include <SFML/Network.hpp>
#include "../libs/rapidjson/document.h"
using namespace rapidjson;
using namespace sf;
class SocketGUI {
    TcpListener listener;
    TcpSocket socket;
    static SocketGUI *singleton;
    static bool initialized;
    SocketGUI();
    void init();
    void receiving();
    static void manageMessage(std::string);
    bool on;
    Mutex send;
    static int popul;
public:
    ~SocketGUI();
    static SocketGUI* getInstance();
    void updateSpeed(unsigned char);
    void detailsSubject(unsigned int id);

};
void exit();
#endif //PROJECTMIDGARDLOGIC_SOCKET_H
