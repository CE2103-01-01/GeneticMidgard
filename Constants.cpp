//
// Created by pablo on 20/04/15.
//


#include "Constants.h"

//TODO: ¿Qué es a?
namespace constants {
    extern const std::string HOME_PATH = getenv("HOME");
    int a = mkdir(PROJECT_PATH, 0777);
}