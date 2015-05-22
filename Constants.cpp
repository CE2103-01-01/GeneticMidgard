//
// Created by pablo on 20/04/15.
//


#include "Constants.h"
#include "libs/pugixml/pugixml.hpp"

using namespace pugi;

namespace constants {

    extern const std::string HOME_PATH = getenv("HOME");
    extern const std::string PROJECT_PATH = HOME_PATH + "/Midgard";
    int creaDirA = mkdir(PROJECT_PATH.c_str(), 0777);
    extern char const *const MAP_FILE = "../res/mapa.tmx";
    extern int RANDOM_WAR_RANGE_BY_EDDA = 50;
}

namespace constantsSubjectXML {
    extern const char* CONSTANT_XML_PATH = "../res/constant.xml";
    extern const char* CONSTANT_AGE = "age";
    extern const char* CONSTANT_XML_ROOT = "CONSTANTS";
    extern const char* GENES_XML_PATH = "../res/genes.xml";
    extern const char* GENES_XML_ROOT = "GENES";
    extern const char* GENES_XML_LENGHT = "CHROMOSOME_LENGHT";
    extern const char* GENES_XML_LENGHT_INFO = "CHR_LEN";
    extern const char* GENES_XML_CHILD = "GENE";
    extern const char* GENES_XML_CHILD_INFO = "GENE_NAME";
    extern const int NUMBER_OF_GENES = loadNumberOfGenes();
}

int loadNumberOfGenes(){
    xml_document genesXMLDoc;
    genesXMLDoc.load_file(constantsSubjectXML::GENES_XML_PATH);
    return genesXMLDoc.child(constantsSubjectXML::GENES_XML_ROOT).child(constantsSubjectXML::GENES_XML_LENGHT).attribute(constantsSubjectXML::GENES_XML_LENGHT_INFO).as_int();
}