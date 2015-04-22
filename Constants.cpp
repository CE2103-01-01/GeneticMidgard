//
// Created by pablo on 20/04/15.
//


#include "Constants.h"

namespace constants {

    extern const std::string homePath = getenv("HOME");
    extern const std::string projectPath = homePath + "/Midgard";
    int a = mkdir(projectPath.c_str(), 0777);
}