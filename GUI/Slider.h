//
// Created by pablo on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_SLIDER_H
#define PROJECTMIDGARDLOGIC_SLIDER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


class RoundRect : public sf::Shape
{
public :

    explicit RoundRect(const sf::Vector2f& radius = sf::Vector2f(0, 0)) :
            m_radius(radius)
    {
        update();
    }

    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }

    virtual unsigned int getPointCount() const
    {
        return 30; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(unsigned int index) const
    {
        static const float pi = 3.141592654f;

        float x;
        float y;
            int offset = m_radius.x - m_radius.y;
            float angle = index * 2 * pi / getPointCount()-pi/2;
            if (angle<pi/2) {
                x = offset  + std::cos(angle) * m_radius.y;
                y = std::sin(angle) * m_radius.y;
            }
            else
            {
                x =  std::cos(angle) * m_radius.y - offset;
                y =  std::sin(angle) * m_radius.y;
            }

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

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
