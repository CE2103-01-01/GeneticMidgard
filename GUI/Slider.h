//
// Created by pablo on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_SLIDER_H
#define PROJECTMIDGARDLOGIC_SLIDER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

/*
 * Figure Needed by Slider
 */
class RoundRect : public sf::Shape
{
public :
    explicit RoundRect();
    explicit RoundRect(const sf::Vector2f& radius);
    void setRadius(const sf::Vector2f& radius);
    const sf::Vector2f& getRadius() const;
    virtual unsigned int getPointCount() const;
    virtual sf::Vector2f getPoint(unsigned int index) const;
private :
    sf::Vector2f m_radius;
};


class Slider {
private:
    int length;
    Vector2f vector;
    unsigned char pos = 0;
    bool init = true;
    RoundRect shape;
    CircleShape circle;
public:
    Slider(Vector2f, int length);
    void drawSlider(RenderTarget&);
    void move(Vector2i);
    unsigned char getPosition();
};

const static Slider NULL_SLIDER(Vector2f(0,0),0);

#endif //PROJECTMIDGARDLOGIC_SLIDER_H
