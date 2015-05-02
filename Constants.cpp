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
    extern const char* CONSTANT_XML_PATH = "../res/constant.xml";
    extern const char* CONSTANT_XML_ROOT = "CONSTANTS";
    extern const char* GENES_XML_PATH = "../res/genes.xml";
    extern const char* GENES_XML_ROOT = "GENES";
    extern const char* GENES_XML_LENGHT = "CHROMOSOME_LENGHT";
    extern const char* GENES_XML_LENGHT_INFO = "CHR_LEN";
    extern const char* GENES_XML_CHILD = "GENE";
    extern const char* GENES_XML_CHILD_INFO = "GENE_NAME";

}