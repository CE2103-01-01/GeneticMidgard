//
// Created by pablo on 03/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_SOCKET_H
#define PROJECTMIDGARDLOGIC_SOCKET_H
static const char *const IP_ADDRESS = "127.0.0.1";

static const int PORT = 53000;

static const float RECONNECT_TIME = 0.5f;

#include <iostream>
#include <SFML/Network.hpp>
using namespace sf;
class SocketGUI {
    TcpSocket socket;
    static SocketGUI *singleton;
    static bool initialized;
    SocketGUI();
    void init();
public:
    static SocketGUI* getInstance();

};

#endif //PROJECTMIDGARDLOGIC_SOCKET_H
