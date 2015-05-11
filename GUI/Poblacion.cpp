//
// Created by pablo on 07/05/15.
//

#include "Poblacion.h"
#include "Map.h"

void Poblacion::drawPoblacion(RenderTarget &target) {
    DoubleListIterator<Person> *iter = poblacion.getIterator();
    //std::cout << poblacion.len() << std::endl;
    while (iter->exists()) {
        Person *next = iter->next();
        Sprite sprite;
        sprite.setTexture(texturePerson);
        sprite.setPosition(sf::Vector2f(Map::getInstance()->getTileWidth() * next->x, Map::getInstance()->getTileHeight() * next->y));
        target.draw(sprite);
        sprite.setTexture(textureLayer);
        sprite.setColor(sf::Color(next->r,next->g,next->b));
        target.draw(sprite);
        LifeUpdate* life =  next->getLifeUpdate();
        if (life) {
            Text text;
            text.setFont(roboto);
            text.setStyle(sf::Text::Bold);
            text.setCharacterSize(12);
            text.setString(to_string(life->life));
            if(life->life==0) text.setString("new");
            text.setPosition(sprite.getPosition());
            text.move(-6,-6);
            if (life->life<0) text.setColor(Color(200,0,0));
            else if(life->life>0) text.setColor(Color(0,200,0));
            else text.setColor(Color(0,0,200));
            target.draw(text);
        }
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
            next->setLifeUpdate(lifeUpdate);
            return;
        }
    }
}

bool Person::operator==(unsigned int pId) {
    return (id==pId);
}

LifeUpdate::LifeUpdate(int life) :life(life){
    startTime = Clock();

}




void Person::setLifeUpdate(int i) {
    if(lifeUpdate)free(lifeUpdate);
    lifeUpdate = new LifeUpdate(i);
}


Poblacion::Poblacion(Texture texture, Texture pTextureLayer) {
    texturePerson = texture;
    textureLayer = pTextureLayer;

    if (!roboto.loadFromFile("../res/roboto.ttf"))
    {
        std::cout << "Error al cargar Roboto Font" << std::endl;
    }

}

LifeUpdate *Person::getLifeUpdate() {
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

Person::Person(unsigned int id, unsigned int x, unsigned int y, unsigned int r, unsigned int g, unsigned int b) : id(id),x(x),y(y),r(r),g(g),b(b)
{
    lifeUpdate = 0;
    lifeUpdate = new LifeUpdate(0);
}
