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
#include "../Data/DoubleList.h"
using namespace sf;
class LifeUpdate{
public:
    LifeUpdate(int life);
    int life;
    Clock startTime;
};
class Person {
public:
    Person(unsigned int id, unsigned int x, unsigned int y, unsigned int r, unsigned int g, unsigned int b) :
            id(id),x(x),y(y),r(r),g(g),b(b) { }
    unsigned int id;
    unsigned int x;
    unsigned int y;
    unsigned int r;
    unsigned int g;
    unsigned int b;
    LifeUpdate* lifeUpdate;
    bool operator==(unsigned int pId);
    void setLifeUpdate(LifeUpdate);

};

class Poblacion {
private:
    DoubleList<Person> poblacion;
    Texture texturePerson;
    Texture textureLayer;

public:
    Poblacion(Texture, Texture);
    void drawPoblacion(RenderTarget&);
    void addPerson(Person&);
    void deletePerson(unsigned int id);
    void updateId(unsigned int id, unsigned int x, unsigned int y);
    void updateLifeId(unsigned int id, int lifeUpdate);
};



#endif //PROJECTMIDGARDLOGIC_POBLACION_H
