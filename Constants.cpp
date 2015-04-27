//
// Created by pablo on 20/04/15.
//


#include "Constants.h"

namespace constants {

    extern const std::string HOME_PATH = getenv("HOME"); //TODO : Buscar usos, pasar a mayucula
    extern const std::string PROJECT_PATH = HOME_PATH + "/Midgard"; //TODO : Buscar usos, pasar a mayucula
    int creaDirA = mkdir(PROJECT_PATH.c_str(), 0777);
    extern char const *const MAP_FILE = "../res/mapa.tmx";

}