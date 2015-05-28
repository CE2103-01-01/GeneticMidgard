//
// Created by pablo on 07/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_POBLACION_H
#define PROJECTMIDGARDLOGIC_POBLACION_H

static const char *const TERRAINS = "terraintypes";

static const char *const TERRAIN_NODE = "terrain";

static const char *const NAME = "name";

static const char *const PERSONA_TERRAIN = "Persona";

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Data/DoubleList.h"
#include "Map.h"
#include "Objects.h"
#include "../Network/SocketGUI.h"

using namespace sf;
class LifeUpdate{
public:
    LifeUpdate(int life);
    int life;
    Clock startTime;
};
class Person : public Object {
public:
    Person(unsigned int id, unsigned int x, unsigned int y, unsigned int r, unsigned int g, unsigned int b) ;
    unsigned int r;
    unsigned int g;
    unsigned int b;
    LifeUpdate* lifeUpdate;
    void setLifeUpdate(int);
    LifeUpdate *getLifeUpdate();

};

class Poblacion: public Objects {
private:
    Mutex objectMutex;
    Texture textureLayer;
    Font roboto;
    //DoubleList<Person> objects;
public:
    Poblacion(Texture, Texture);
    void drawObjects(RenderTarget &target, const IntRect &rect);
    void updateLifeId(unsigned int id, int lifeUpdate);
    void clickOnPerson(Vector2f);

};



#endif //PROJECTMIDGARDLOGIC_POBLACION_H
