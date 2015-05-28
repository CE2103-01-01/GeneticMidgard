//
// Created by root on 30/04/15.
//

#ifndef PROJECTMIDGARD_MOVILOBJECTMANAGER_H
#define PROJECTMIDGARD_MOVILOBJECTMANAGER_H

#define OBJECT_ID 8888
#define OBJECT_ID_MULTIPLIER  10000

#include "Subject.h"
#include "Terrain.h"

#define NUMBER_OF_OBJECTS 30

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
    movilObject* listObject;
    int* listXmlData;
    static movilObjectManager* instance;
    int firstEmpty;
    int elementCounter;
public:
    static movilObjectManager* getInstance();
    movilObjectManager();
    void update();
    void decreseCounter(movilObject);
    void obtainData();
    bool needsToUpdate();
    movilObject getDataByPosistion(Vector2D);
    movilObject* getRandomObject();
};
/** Clase movilObject
 * @brief clase de los objetos generado por el Manager
 *
 *
*/
class movilObject {
private:
    Vector2D position;
    int effect;
    int object;
    bool use;
    int id;
    int isEmptyVar;
    int positionOnList;
public:
    bool operator ==(movilObject);
    movilObject(int,int,int,int,int,int);
    ~movilObject();
    void applyEffect(Subject* person);
    int getId();
    int get_X_Position();
    int get_Y_Position();
    int getEffect();
    int getCharacteristic();
    Vector2D getVector();
    int isEmpty();
    int getPositionOnList();
    void freeSpace(int);
};


#endif //PROJECTMIDGARD_MOVILOBJECTMANAGER_H
