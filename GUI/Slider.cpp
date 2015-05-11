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
