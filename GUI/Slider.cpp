//
// Created by pablo on 10/05/15.
//

#include "Slider.h"
#include "../Network/SocketGUI.h"
/*
 * Constructor of Slider
 */
Slider::Slider(Vector2f vector, int length): length(length), vector(vector) {

}

void Slider::drawSlider(RenderTarget &target) {
    double height = length * 0.2;
    if (init) {
        //Outline
        shape = RoundRect(Vector2f(length, height));
        shape.setFillColor(sf::Color(255, 255, 255, 0));// Nothing inside
        shape.setOutlineThickness(length * 0.05);
        int alpha = 200;
        shape.setOutlineColor(sf::Color(255, 255, 255, alpha));
        shape.setPosition(vector);
        //Inside Circle
        circle = CircleShape(height);
        circle.setFillColor(sf::Color(50, 50, 50, alpha));

        init = false;
    }
    circle.setPosition(vector.x + (2 * (pos / 255.0f) * (length - height)), vector.y);
    target.draw(shape);
    target.draw(circle);


}
/*
 * Receives the vector of mouse position and updates the pos of the slider
 */
void Slider::move(Vector2i i) {
    if(shape.getGlobalBounds().contains(Vector2f(i.x, i.y)))
    {
        float xSlider =shape.getGlobalBounds().left;
        int posCalc = 255* (i.x-xSlider)/(length*2.0f);
        if (posCalc>255) return;
        pos = posCalc;
        SocketGUI::getInstance()->updateSpeed(pos);
    }

}/*
 * Position from 1 to 255
 */
unsigned char Slider::getPosition() {
    return pos;
}
RoundRect::RoundRect()
{
    m_radius = Vector2f(0,0);
    update();
}
RoundRect::RoundRect(const sf::Vector2f& radius) : m_radius(radius)
{
    update();
}

void RoundRect::setRadius(const sf::Vector2f &radius) {
    m_radius = radius;
    update();
}

const sf::Vector2f &RoundRect::getRadius() const {
    return m_radius;
}

unsigned int RoundRect::getPointCount() const {
    return 30;
}

sf::Vector2f RoundRect::getPoint(unsigned int index) const {
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
