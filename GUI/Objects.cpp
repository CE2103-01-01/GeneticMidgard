//
// Created by pablo on 27/05/15.
//

#include "Objects.h"
#include "Map.h"

bool Object::operator==(unsigned int pId) {
    return (id==pId);
}

void Objects::addObject(Object &object) {
    objectMutex.lock();
    objects.add(object);
    objectMutex.unlock();
}

void Objects::deleteObject(unsigned int id) {
    int i=0;
    DoubleListIterator<Object> *iter = objects.getIterator();
    while (iter->exists())
    {
        if(*(iter->next())==(id)) {
            objects.deleteNode(i);
            return;
        }
        i++;
    }

}

void Objects::updateId(unsigned int id, unsigned int x, unsigned int y) {
    int i=0;
    DoubleListIterator<Object> *iter = objects.getIterator();
    while (iter->exists()) {
        Object *next = iter->next();
        if(*next==id)
        {
            next->x = x;
            next->y = y;
            return;
        }
    }

}

Objects::Objects(Texture texture) {
    objects = DoubleList<Object>();
    textureObject = texture;
}

void Objects::drawObjects(RenderTarget &target, const IntRect &rect) {
    objectMutex.lock();
    DoubleListIterator<Object> *iter = objects.getIterator();
    while (iter->exists()) {
        Object *next = iter->next();
        // if(rect.contains(Vector2i(next->x,next->y)))continue;
        Sprite sprite;
        sprite.setTexture(textureObject);
        sprite.setPosition(sf::Vector2f(Map::getInstance()->getTileWidth() * next->x, Map::getInstance()->getTileHeight() * next->y));
        target.draw(sprite);
    }
    objectMutex.unlock();
}

Object::Object(unsigned int id, unsigned int x, unsigned int y) :id(id), x(x), y(y){

}

Object::Object() {

}
