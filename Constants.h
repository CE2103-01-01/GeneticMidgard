//
// Created by pablo on 20/04/15.
//

#ifndef PROJECTMIDGARD_CONSTANTS_H
#define PROJECTMIDGARD_CONSTANTS_H

#define TREE_SIZE 150
#define SUBJECTS_BY_GENERATION 20
#define GENE_LEN_ON_BYTES 1
#define NUMBER_OF_CHARACTERISTICS 8
#define POSITION_OF_AGE 0
#define POSITION_OF_EXPERIENCE 1
#define POSITION_OF_HEALTH 2
#define POSITION_OF_ATTACK 3
#define POSITION_OF_SPEED 2
#define POSITION_OF_DEFENSE 4
#define POSITION_OF_INTELLIGENCE 5
#define POSITION_OF_MAGIC 6
#define POSITION_OF_RUNES 7
#define POSITION_OF_ENERGY 8
#define POSITION_OF_BLOT 9
#define POSITION_OF_SUPERSTITION 10
#define POSITION_OF_ARMOR 11
#define POSITION_OF_WEAPON 12
#define POSITION_OF_RED 13
#define POSITION_OF_GREEN 14
#define POSITION_OF_BLUE 15

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
