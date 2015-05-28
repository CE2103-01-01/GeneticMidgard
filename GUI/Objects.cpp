//
// Created by pablo on 27/05/15.
//

#include "Objects.h"


bool Object::operator==(unsigned int pId) {
    return (id==pId);
}

void Objects::addObject(Object &object) {
    objectMutex.lock();
    std::cout << "HEy" << std::endl;
    objects.add(object);
    objectMutex.unlock();
}

void Objects::deleteObject(unsigned int id) {
    objectMutex.lock();
    int i=0;
    DoubleListIterator<Object> *iter = objects.getIterator();
    while (iter->exists())
    {
        if(*(iter->next())==(id)) {
            objects.deleteNode(i);
            objectMutex.unlock();
            return;
        }
        i++;
    }
    objectMutex.unlock();
}

void Objects::updateId(unsigned int id, unsigned int x, unsigned int y) {
    objectMutex.lock();
    int i=0;
    DoubleListIterator<Object> *iter = objects.getIterator();
    while (iter->exists()) {
        Object *next = iter->next();
        if(*next==id)
        {
            next->x = x;
            next->y = y;
            objectMutex.unlock();
            return;
        }
    }
    objectMutex.unlock();
}

Objects::Objects(Texture texture) {
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


