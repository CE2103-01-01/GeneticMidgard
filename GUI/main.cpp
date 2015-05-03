//
// Created by pablo on 01/05/15.
//

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Map.h"


using namespace sf;
using namespace gui_constants;
int main()
{
    Map mapa = Map();
    mapa.loadTerrain();
    RenderWindow window(sf::VideoMode::getDesktopMode(), WINDOW_NAME);
    unsigned int heightScreen = window.getSize().y;
    unsigned int widthScreen = window.getSize().x;
    sf::View mapView;
    mapView.reset(FloatRect(0,0,widthScreen,heightScreen));
    mapView.setViewport(FloatRect(0.0f,0.0f,1.0f,1.0f));
    Vector2f position(0,0);

    float yMax = mapa.getHeight()*mapa.getTileHeight()-mapView.getSize().y/2;
    float yMin = mapView.getSize().y/2;
    float xMax = mapa.getWidth()*mapa.getTileWidth()-mapView.getSize().x/2;
    float xMin = mapView.getSize().x/2;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // catch the resize events
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::MouseWheelMoved) {

                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    mapView.move(0, event.mouseWheel.delta * 5);
                }
                else mapView.move(-event.mouseWheel.delta * 5, 0);

                if (mapView.getCenter().y > yMax)
                    mapView.setCenter(mapView.getCenter().x, yMax);
                if (mapView.getCenter().y < yMin)
                    mapView.setCenter(mapView.getCenter().x, yMin);
                if (mapView.getCenter().x > xMax)
                    mapView.setCenter(xMax, mapView.getCenter().y);
                if (mapView.getCenter().x < xMin)
                    mapView.setCenter(xMin, mapView.getCenter().x);
            }
        }
        window.setView(mapView);
        window.clear();

        mapa.renderMap(&window);

        window.display();
    }


    return 0;
}