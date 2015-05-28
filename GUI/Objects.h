//
// Created by pablo on 27/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_OBJECT_H
#define PROJECTMIDGARDLOGIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include "../Data/DoubleList.h"

using namespace sf;
class LifeUpdate{
public:
    LifeUpdate(int life);
    int life;
    Clock startTime;
};
class Object
{
public:
    Object(unsigned int id, unsigned int x, unsigned int y);
    Object(unsigned int id, unsigned int x, unsigned int y, unsigned int r, unsigned int g, unsigned int b) ;
    unsigned int id;
    unsigned int x;
    unsigned int y;
    unsigned int r;
    unsigned int g;
    unsigned int b;
    bool operator==(unsigned int pId);
    LifeUpdate* lifeUpdate;
    void setLifeUpdate(int);
    LifeUpdate *getLifeUpdate();
};
class Objects {
protected:
    Mutex objectMutex;
    DoubleList<Object> objects;
    Texture textureObject;
public:
    Objects(Texture);
    void drawObjects(RenderTarget&,const IntRect &);
    void addObject(Object&);
    void deleteObject(unsigned int id);
    void updateId(unsigned int id, unsigned int x, unsigned int y);
};




#endif //PROJECTMIDGARDLOGIC_OBJECT_H
