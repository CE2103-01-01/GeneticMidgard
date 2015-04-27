//
// Created by pablo on 20/04/15.
//

#ifndef PROJECTMIDGARD_CONSTANTS_H
#define PROJECTMIDGARD_CONSTANTS_H

#define TREE_SIZE 50
#define GENE_LEN_ON_BYTES 1
#define GENES_XML_PATH "genes.xml"
#define GENES_XML_ROOT "GENES"
#define GENES_XML_LENGHT "CHROMOSOME_LENGHT"
#define GENES_XML_LENGHT_INFO "CHR_LEN"
#define GENES_XML_CHILD "GENE"
#define GENES_XML_CHILD_INFO "NAME"
#define PROJECT_PATH "/Midgard"

//TODO: estas bibliotecas se estan incluyendo en muchos archivos donde no se ocupan y hacen el codigo mas pesado,
// se debe buscar su uso y separarlo...
#include <fstream>
#include <sys/stat.h>
//TODO: estas bibliotecas se estan incluyendo en muchos archivos donde no se ocupan y hacen el codigo mas pesado,
// se debe buscar su uso y separarlo...

namespace constants {
    extern const std::string HOME_PATH; //TODO : Buscar usos, pasar a mayucula
}

#endif //PROJECTMIDGARD_CONSTANTS_H
