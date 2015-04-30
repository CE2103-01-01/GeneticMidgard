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

namespace constantsSubjectXML {
    extern const char* CONSTANT_XML_PATH = "constant.xml";
    extern const char* CONSTANT_XML_ROOT = "CONSTANTS";
    extern const char* GENES_XML_PATH = "genes.xml";
    extern const char* GENES_XML_ROOT = "GENES";
    extern const char* GENES_XML_LENGHT = "CHROMOSOME_LENGHT";
    extern const char* GENES_XML_LENGHT_INFO = "CHR_LEN";
    extern const char* GENES_XML_CHILD = "GENE";
    extern const char* GENES_XML_CHILD_INFO = "NAME";
    extern const char* AGE_XML = "age";
    extern const char* EXPERIENCE_XML = "experience";
    extern const char* HEALTH_XML = "health";
    extern const char* ATTACK_XML = "attack";
    extern const char* SPEED_XML = "speed";
    extern const char* DEFENSE_XML = "defense";
    extern const char* INTELLIGENCE_XML = "intelligence";
    extern const char* MAGIC_XML = "magic";
    extern const char* RUNES_XML = "runes";
    extern const char* BLOT_XML = "blot";
    extern const char* SUPERSTITION_XML = "superstition";
}