//
// Created by pablo on 03/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_SOCKET_H
#define PROJECTMIDGARDLOGIC_SOCKET_H
static const char *const IP_ADDRESS = "127.0.0.1";

static const int PORT = 53000;

static const float RECONNECT_TIME = 1.0f;

#include <iostream>
#include <SFML/Network.hpp>
#include "../libs/rapidjson/document.h"
using namespace rapidjson;
using namespace sf;
class SocketGUI {
    TcpSocket socket;
    static SocketGUI *singleton;
    static bool initialized;
    SocketGUI();
    void init();
    void receiving();
    static void manageMessage(std::string);
public:
    static SocketGUI* getInstance();

};

#endif //PROJECTMIDGARDLOGIC_SOCKET_H
