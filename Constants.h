//
// Created by pablo on 20/04/15.
//

#ifndef PROJECTMIDGARD_CONSTANTS_H
#define PROJECTMIDGARD_CONSTANTS_H

#define TREE_SIZE 100

#define UNION_AGE 4
#define TWILIGHT_OF_THE_GODS_AGE 5

#define INITIAL_NUMBER_OF_POPULATIONS 40
#define INITIAL_NUMBER_OF_SUBJECTS 50
#define SUBJECTS_BY_GENERATION 25
#define RANDOM_WAR_LIMIT 100
#define MAX_YEARS 100

#define SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID 1000

#define LIMIT_LEVEL_ONE 100
#define LIMIT_LEVEL_TWO 150
#define LIMIT_LEVEL_THREE 200

#define ATTACK_DAMAGE -2

#define GENE_LEN_ON_BYTES 1
#define POSITION_OF_GENE_LIFE 0
#define POSITION_OF_GENE_ATTACK 1
#define POSITION_OF_GENE_DEFENSE 2
#define POSITION_OF_GENE_MAGIC 3
#define POSITION_OF_GENE_INTELLIGENCE 4
#define POSITION_OF_GENE_SUPERSTITION 5
#define POSITION_OF_GENE_SPEED 6
#define POSITION_OF_GENE_VITAL_ENERGY 7
#define POSITION_OF_GENE_BLOT 8
#define POSITION_OF_GENE_RUNES 9
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
    extern int RANDOM_WAR_RANGE_BY_EDDA;
}

namespace constantsSubjectXML {
    extern const char* CONSTANT_XML_PATH;
    extern const char* CONSTANT_AGE;
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
