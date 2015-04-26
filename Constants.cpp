//
// Created by pablo on 20/04/15.
//


#include "Constants.h"
#include <stdlib.h>
#include <iosfwd>
#include <fstream>
#include <sys/stat.h>

namespace constants {

    extern const std::string homePath = getenv("HOME"); //TODO : Buscar usos, pasar a mayucula
    extern const std::string projectPath = homePath + "/Midgard"; //TODO : Buscar usos, pasar a mayucula
    int a = mkdir(projectPath.c_str(), 0777);   //TODO : ¿QUE ES a?

}