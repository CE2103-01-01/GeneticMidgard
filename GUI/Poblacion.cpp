//
// Created by pablo on 07/05/15.
//

#include "Poblacion.h"
#include "../Network/SocketGUI.h"


void Poblacion::drawObjects(RenderTarget &target, const IntRect &rect) {
    objectMutex.lock();
    DoubleListIterator<Object> *iter = objects.getIterator();

    while (iter->exists()) {
        Object *next = iter->next();
       // if(rect.contains(Vector2i(next->x,next->y)))continue;
        Sprite sprite;
        sprite.setTexture(textureObject);
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
    objectMutex.unlock();
}



void Poblacion::updateLifeId(unsigned int id, int lifeUpdate) {
    int i=0;
    DoubleListIterator<Object> *iter = objects.getIterator();
    while (iter->exists()) {
        Object *next = iter->next();
        if(*next==id)
        {
            next->setLifeUpdate(lifeUpdate);
            return;
        }
    }
}







Poblacion::Poblacion(Texture texture, Texture pTextureLayer) {
    textureObject = texture;
    textureLayer = pTextureLayer;

    if (!roboto.loadFromFile("../res/roboto.ttf"))
    {
        std::cout << "Error al cargar Roboto Font" << std::endl;
    }

}

/**
 * Check if anyone is on the mouse click and tell the logic that.
 */
void Poblacion::clickOnPerson(Vector2f click) {
    int x = (click.x/Map::getInstance()->tileWidth);
    int y = (click.y/Map::getInstance()->tileHeight);
    if (x<0||y<0||x>=Map::getInstance()->getWidth()||y>=Map::getInstance()->getHeight())return;
    DoubleListIterator<Object> *iter  = objects.getIterator();
    while (iter->exists())
    {
        Object *next = iter->next();
        if(next->x==click.x && next->y==click.y)
        {
            SocketGUI::getInstance()->detailsSubject(next->id);
            break;
        }
    }
}
