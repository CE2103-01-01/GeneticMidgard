//
// Created by root on 30/04/15.
//

#ifndef PROJECTMIDGARD_MOVILOBJECTMANAGER_H
#define PROJECTMIDGARD_MOVILOBJECTMANAGER_H


#include "Subject.h"
#include "Terrain.h"

/** Clase movilObjectManager
 * @brief clase a la cual pertenecen todos los objetos
 * @caracteristicas: depende parametros de archivo xml
 *
*/
class movilObject;
class movilObjectManager{
private:
    int objectCounter;
    DoubleList<movilObject> listObject;
public:
    movilObjectManager();
    void createObject();
    void decreseCounter();
};
/** Clase movilObject
 * @brief clase de los objetos generado por el Manager
 *
 *
*/
class movilObject {
private:
    movilObjectManager* manager;
    Vector2D* position;
    int effect;
    std::string type;
    int object;
    bool use;
    int id;
public:
    movilObject(movilObjectManager*,std::string,int,int,int,int,int);
    ~movilObject();
    void applyEffect(Subject* person);
    int getId();
    std::string getType();
    int get_X_Position();
    int get_Y_Position();

};


#endif //PROJECTMIDGARD_MOVILOBJECTMANAGER_H
