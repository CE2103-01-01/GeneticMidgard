//
// Created by root on 30/04/15.
//

#ifndef PROJECTMIDGARD_MOVILOBJECTMANAGER_H
#define PROJECTMIDGARD_MOVILOBJECTMANAGER_H


#include "Subject.h"
#include "Chromosome.h"
/** Clase movilObjectManager
 * @brief clase a la cual pertenecen todos los objetos
 * @caracteristicas: depende parametros de archivo xml
 *
*/
class movilObjectManager{
private:
    int objectCounter;
public:
    movilObjectManager();
    void createObject();
    void decreseCounter();
};
class movilObject {
private:
    movilObjectManager* manager;
    int effect;
    std::string type;
    int object;
    bool use;
public:
    movilObject(movilObjectManager*,std::string,int,int);
    ~movilObject();
    void applyEffect(Subject* person);
    std::string getType();

};


#endif //PROJECTMIDGARD_MOVILOBJECTMANAGER_H
