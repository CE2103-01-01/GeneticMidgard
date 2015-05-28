//
// Created by pablo on 27/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_OBJECT_H
#define PROJECTMIDGARDLOGIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include "../Data/DoubleList.h"
#include "Map.h"
using namespace sf;

class Object {
public:
    Object(unsigned int id, unsigned int x, unsigned int y) ;
    unsigned int id;
    unsigned int x;
    unsigned int y;
    bool operator==(unsigned int pId);

};
class Objects {
private:
    DoubleList<Object> objects;
    Texture textureObject;
    Mutex objectMutex;

public:
    Objects(Texture);
    void drawObjects(RenderTarget&,const IntRect &);
    void addObject(Object&);
    void deleteObject(unsigned int id);
    void updateId(unsigned int id, unsigned int x, unsigned int y);
};




#endif //PROJECTMIDGARDLOGIC_OBJECT_H
