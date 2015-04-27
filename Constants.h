//
// Created by pablo on 20/04/15.
//

#ifndef PROJECTMIDGARD_CONSTANTS_H
#define PROJECTMIDGARD_CONSTANTS_H

#define TREE_SIZE 50

#include <stdlib.h>
#include <iosfwd>
#include <fstream>
#include <sys/stat.h>

namespace constants {
    extern const std::string HOME_PATH; //TODO : Buscar usos, pasar a mayucula
    extern const std::string PROJECT_PATH; //TODO : Buscar usos, pasar a mayucula
    extern char const *const MAP_FILE;
}

enum Gene{InmuneSystem, Inteligence, Attack, Defense, VitalEnergy, Blot, Runes, Superstition, lenght};

#endif //PROJECTMIDGARD_CONSTANTS_H
