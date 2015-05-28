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
    objectMutex.lock();
    int i=0;
    DoubleListIterator<Object> *iter = objects.getIterator();
    while (iter->exists())
    {
        if(*(iter->next())==(id)) {
            std::cout << "Borrar" << std::endl;
            objects.deleteNode(i);
            std::cout << "Last:" << objects.len() << std::endl;
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


void Object::setLifeUpdate(int i) {
    if(lifeUpdate)free(lifeUpdate);
    lifeUpdate = new LifeUpdate(i);
}


LifeUpdate *Object::getLifeUpdate() {
    if (lifeUpdate)
    {
        float elapsedSeconds = lifeUpdate->startTime.getElapsedTime().asSeconds();
        if (elapsedSeconds < 1.0f)
        {
            return lifeUpdate;
        }
        else
        {
            free(lifeUpdate);
            lifeUpdate = nullptr;
        }
    }
    return nullptr;
}

LifeUpdate::LifeUpdate(int life) :life(life){
    startTime = Clock();

}



Object::Object(unsigned int pId, unsigned int pX, unsigned int pY, unsigned int pR, unsigned int pG, unsigned int pB)
{
    id=pId; x = pX; y = pY; r = pR; g = pG; b = pB;
    lifeUpdate = 0;
    lifeUpdate = new LifeUpdate(0);
}
