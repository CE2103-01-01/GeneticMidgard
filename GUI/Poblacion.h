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

class Poblacion: public Objects {
private:
    Mutex objectMutex;
    Texture textureLayer;
    Font roboto;
public:
    Poblacion(Texture, Texture);
    void drawObjects(RenderTarget &target, const IntRect &rect);
    void updateLifeId(unsigned int id, int lifeUpdate);
    void clickOnPerson(Vector2f);

};



#endif //PROJECTMIDGARDLOGIC_POBLACION_H
