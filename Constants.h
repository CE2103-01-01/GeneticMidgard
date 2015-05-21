//
// Created by pablo on 20/04/15.
//

#ifndef PROJECTMIDGARD_CONSTANTS_H
#define PROJECTMIDGARD_CONSTANTS_H

#define TREE_SIZE 100

#define INITIAL_NUMBER_OF_POPULATIONS 5
#define INITIAL_NUMBER_OF_SUBJECTS 20
#define SUBJECTS_BY_GENERATION 5

#define GENE_LEN_ON_BYTES 1
#define POSITION_OF_GENE_LIFE 0
#define POSITION_OF_GENE_ATTACK 1
#define POSITION_OF_GENE_DEFENSE 2
#define POSITION_OF_GENE_SPEED 3
#define POSITION_OF_GENE_INTELLIGENCE 4
#define POSITION_OF_GENE_MAGIC 5
#define POSITION_OF_GENE_VITAL_ENERGY 6
#define POSITION_OF_GENE_BLOT 7
#define POSITION_OF_GENE_RUNES 8
#define POSITION_OF_GENE_SUPERSTITION 9
#define POSITION_OF_GENE_RED 10
#define POSITION_OF_GENE_GREEN 11
#define POSITION_OF_GENE_BLUE 12

#define NUMBER_OF_CHARACTERISTICS 6
#define POSITION_OF_CHARACTERISTIC_LIFE 0
#define POSITION_OF_CHARACTERISTIC_AGE 1
#define POSITION_OF_CHARACTERISTIC_EXPERIENCE 2
#define POSITION_OF_CHARACTERISTIC_WEAPON 3
#define POSITION_OF_CHARACTERISTIC_ARMOR 4
#define POSITION_OF_CHARACTERISTIC_PROFESSION 5

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
