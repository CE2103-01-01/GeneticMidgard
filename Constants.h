//
// Created by pablo on 20/04/15.
//

#ifndef PROJECTMIDGARD_CONSTANTS_H
#define PROJECTMIDGARD_CONSTANTS_H

#define TREE_SIZE 100
#define INITIAL_NUMBER_OF_POPULATIONS 5
#define SUBJECTS_BY_GENERATION 20
#define GENE_LEN_ON_BYTES 1
#define NUMBER_OF_CHARACTERISTICS 17
#define NUMBER_OF_NON_GENETIC_CHARACTERISCTICS 7
#define POSITION_OF_LIFE 0
#define POSITION_OF_ATTACK 1
#define POSITION_OF_DEFENSE 2
#define POSITION_OF_SPEED 3
#define POSITION_OF_INTELLIGENCE 4
#define POSITION_OF_MAGIC 5
#define POSITION_OF_VITAL_ENERGY 6
#define POSITION_OF_BLOT 7
#define POSITION_OF_RUNES 8
#define POSITION_OF_SUPERSTITION 9
#define POSITION_OF_RED 10
#define POSITION_OF_GREEN 11
#define POSITION_OF_BLUE 12
#define POSITION_OF_AGE 13
#define POSITION_OF_EXPERIENCE 14
#define POSITION_OF_WEAPON 15
#define POSITION_OF_ARMOR 16

//TODO: estas bibliotecas se estan incluyendo en muchos archivos donde no se ocupan y hacen el codigo mas pesado, se debe buscar su uso y separarlo...
#include <fstream>
#include <sys/stat.h>

//TODO: estas bibliotecas se estan incluyendo en muchos archivos donde no se ocupan y hacen el codigo mas pesado, se debe buscar su uso y separarlo...

namespace constants {
    extern const std::string HOME_PATH;
    extern const std::string PROJECT_PATH;
    extern char const *const MAP_FILE;
}

namespace constantsSubjectXML {
    extern const char* CONSTANT_XML_PATH;
    extern const char* CONSTANT_XML_ROOT;
    extern const char* GENES_XML_PATH;
    extern const char* GENES_XML_ROOT;
    extern const char* GENES_XML_LENGHT;
    extern const char* GENES_XML_LENGHT_INFO;
    extern const char* GENES_XML_CHILD;
    extern const char* GENES_XML_CHILD_INFO;
    extern const int NUMBER_OF_GENES;
}

int loadNumberOfGenes();

#endif //PROJECTMIDGARD_CONSTANTS_H
