//
// Created by roberto on 25/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_BIRTHWRITER_H
#define PROJECTMIDGARDLOGIC_BIRTHWRITER_H

#include <iostream>
#include <fstream>
#include "../Constants.h"

#define EXTENSION ".birth"
#define PATH "/"


class FileManager{
public:
    static void writeFile(const char*, int, int);
    static void readFile(char*, int, int);
    static void deleteFile(int);
};


#endif //PROJECTMIDGARDLOGIC_BIRTHWRITER_H
