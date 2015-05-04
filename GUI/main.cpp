//
// Created by pablo on 01/05/15.
//

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Map.h"
#include "../Network/SocketGUI.h"


static const int SCROLL_SPEED = 10;

static const float STEPMOVE = 35.f;

void checkViewLimits(View &mapView, View &minimap, float yMax, float yMin, float xMax, float xMin);

using namespace sf;
using namespace gui_constants;
int main()
{
    Thread thread(&SocketGUI::getInstance);//Init Connection
    thread.launch();

    cout<<"GUI:..."<<endl;
    string a;
    cin>>a;
    Map mapa = Map();
    mapa.loadTerrain();
    RenderWindow window(sf::VideoMode::getDesktopMode(), WINDOW_NAME);
    window.setFramerateLimit(60);
    unsigned int heightScreen = window.getSize().y;
    unsigned int widthScreen = window.getSize().x;
    //Original View
    sf::View fixed = window.getView();
    sf::View mapView(FloatRect(0,0,widthScreen,heightScreen));
    //Minimap
    unsigned int size = 300;
    sf::View minimap(sf::FloatRect(fixed.getCenter().x, fixed.getCenter().y, static_cast<float>(size), static_cast<float>(window.getSize().y*size/window.getSize().x)));
    minimap.setViewport(sf::FloatRect(1.f-static_cast<float>(minimap.getSize().x)/window.getSize().x-0.02f, 1.f-static_cast<float>(minimap.getSize().y)/window.getSize().y-0.02f, static_cast<float>(minimap.getSize().x)/window.getSize().x, static_cast<float>(minimap.getSize().y)/window.getSize().y));
    minimap.zoom(12.f);
    mapView.setViewport(FloatRect(0.0f,0.0f,1.0f,1.0f));

    RenderTexture mapText;
    if(!mapText.create(mapa.getHeight()*mapa.getTileHeight(),mapa.getWidth()*mapa.getTileWidth())) abort;

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
            else if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            else if (event.type == sf::Event::MouseWheelMoved) {

                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    mapView.move(0, event.mouseWheel.delta * SCROLL_SPEED);
                    minimap.move(0, event.mouseWheel.delta * SCROLL_SPEED);
                }
                else {
                    mapView.move(-event.mouseWheel.delta * SCROLL_SPEED, 0);
                    minimap.move(-event.mouseWheel.delta * SCROLL_SPEED, 0);
                }

                checkViewLimits(mapView, minimap, yMax, yMin, xMax, xMin);
            }
            else if( event.type == sf::Event::KeyPressed )
            {
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S){
                    mapView.move(0, STEPMOVE);
                    minimap.move(0, STEPMOVE);
                }
                else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W){
                    mapView.move(0, -STEPMOVE);
                    minimap.move(0, -STEPMOVE);
                }
                else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D){
                    mapView.move(STEPMOVE,0);
                    minimap.move(STEPMOVE,0);
                }
                else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A){
                    mapView.move(-STEPMOVE,0);
                    minimap.move(-STEPMOVE,0);
                }
                checkViewLimits(mapView,minimap, yMax, yMin, xMax, xMin);
            }
        }
        mapText.clear();
        window.clear();
        window.setView(mapView);
        mapa.renderMap(mapText);
        mapText.display();
        window.draw(Sprite(mapText.getTexture()));
        window.setView(minimap);
        window.draw(Sprite(mapText.getTexture()));
        window.display();
    }


    return 0;
}

void checkViewLimits(View &mapView,View &minimap, float yMax, float yMin, float xMax, float xMin) {
    if (mapView.getCenter().y > yMax)
    {
        mapView.setCenter(mapView.getCenter().x, yMax);
        minimap.setCenter(minimap.getCenter().x, yMax);
    }
    else if (mapView.getCenter().y < yMin) {
        mapView.setCenter(mapView.getCenter().x, yMin);
        minimap.setCenter(mapView.getCenter().x, yMin);
    }
    else if (mapView.getCenter().x > xMax) {
        mapView.setCenter(xMax, mapView.getCenter().y);
        minimap.setCenter(xMax, mapView.getCenter().y);
    }
    else if (mapView.getCenter().x < xMin) {
        mapView.setCenter(xMin, mapView.getCenter().y);
        minimap.setCenter(xMin, mapView.getCenter().y);
    }

}