//
// Created by pablo on 07/05/15.
//

#include "Poblacion.h"
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"
#include "Map.h"

void Poblacion::drawPoblacion(RenderTarget &target) {
    DoubleListIterator<Person> *iter = poblacion.getIterator();
    while (iter->exists()) {
        Person *next = iter->next();
        Sprite sprite;
        sprite.setTexture(texturePerson);
        sprite.setPosition(sf::Vector2f(Map::tileWidth * next->x, Map::tileHeight * next->y));
        target.draw(sprite);
        sprite.setTexture(textureLayer);
        sprite.setColor(sf::Color(next->r,next->g,next->b));
        target.draw(sprite);
    }
}

void Poblacion::addPerson(Person &person) {
    poblacion.add(person);
}

void Poblacion::deletePerson(unsigned int id) {
    int i=0;
    DoubleListIterator<Person> *iter = poblacion.getIterator();
    while (iter->exists())
    {
        if(*(iter->next())==(id)) {
            poblacion.deleteNode(i);
            return;
        }
        i++;
    }

}

void Poblacion::updateId(unsigned int id, unsigned int x, unsigned int y) {
    int i=0;
    DoubleListIterator<Person> *iter = poblacion.getIterator();
    while (iter->exists()) {
        Person *next = iter->next();
        if(*next==id)
        {
            next->x = x;
            next->y = y;
            return;
        }
    }

}

void Poblacion::updateLifeId(unsigned int id, int lifeUpdate) {
    int i=0;
    DoubleListIterator<Person> *iter = poblacion.getIterator();
    while (iter->exists()) {
        Person *next = iter->next();
        if(*next==id)
        {
            next->setLifeUpdate(LifeUpdate(lifeUpdate));
            return;
        }
    }
}

bool Person::operator==(unsigned int pId) {
    return (id==pId);
}

LifeUpdate::LifeUpdate(int life) {
    startTime = Clock();
}

void Person::setLifeUpdate(LifeUpdate update) {
    lifeUpdate = static_cast<LifeUpdate*>(malloc(sizeof(update)));
    new(lifeUpdate) LifeUpdate(update);
}

Poblacion::Poblacion(Texture texture, Texture pTextureLayer) {
    texturePerson = texture;
    textureLayer = pTextureLayer;
}
