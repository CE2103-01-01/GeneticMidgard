//
// Created by root on 30/04/15.
//

#ifndef PROJECTMIDGARD_MOVILOBJECTMANAGER_H
#define PROJECTMIDGARD_MOVILOBJECTMANAGER_H

#define OBJECT_ID 8888
#define OBJECT_ID_MULTIPLIER  10000

#include "Subject.h"
#include "Terrain.h"
#include "MovilObject.h"

#define NUMBER_OF_OBJECTS 30

class MovilObject;
void* managerThread(void*);

/** Clase MovilObjectManager
 * @brief clase a la cual pertenecen todos los objetos
 * @caracteristicas: depende parametros de archivo xml
 *
*/

class MovilObjectManager{
    pthread_t* updateThread;
    int idCounter;
    int objectCounter;
    MovilObject* listObject;
    int* listXmlData;
    static MovilObjectManager* instance;
    int firstEmpty;
    int elementCounter;
public:
    MovilObjectManager();
    ~MovilObjectManager();
    static MovilObjectManager* getInstance();
    void update();
    void decreseCounter(MovilObject);
    bool needsToUpdate();
    MovilObject getDataByPosistion(Vector2D);
    MovilObject* getRandomObject();
};


#endif //PROJECTMIDGARD_MOVILOBJECTMANAGER_H
