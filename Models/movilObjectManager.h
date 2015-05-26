//
// Created by root on 30/04/15.
//

#ifndef PROJECTMIDGARD_MOVILOBJECTMANAGER_H
#define PROJECTMIDGARD_MOVILOBJECTMANAGER_H

#define OBJECT_ID 8888
#define OBJECT_ID_MULTIPLIER  10000

#include "Subject.h"
#include "Terrain.h"

void* managerThread(void*);

class movilObject;
/** Clase movilObjectManager
 * @brief clase a la cual pertenecen todos los objetos
 * @caracteristicas: depende parametros de archivo xml
 *
*/

class movilObjectManager{
    int idCounter;
    int objectCounter;
    DoubleList<movilObject> listObject;
    DoubleList<xml_node> listXmlData;
    int listSize;
    static movilObjectManager* instance;
public:
    static movilObjectManager* getInstance();
    movilObjectManager();
    void update();
    void decreseCounter(movilObject);
    void obtainData();
    bool needsToUpdate();
    movilObject getDataByPosistion(Vector2D);
    movilObject getRandomObject();
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
    int object;
    bool use;
    int id;
public:
    bool operator ==(movilObject);
    movilObject(movilObjectManager*,int,int,int,int,int);
    ~movilObject();
    void applyEffect(Subject* person);
    int getId();
    std::string getType();
    int get_X_Position();
    int get_Y_Position();
    Vector2D* getVector();

};


#endif //PROJECTMIDGARD_MOVILOBJECTMANAGER_H
