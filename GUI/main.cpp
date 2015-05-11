//
// Created by pablo on 01/05/15.
//

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Map.h"
#include "../Network/SocketGUI.h"
#include "Slider.h"


static const int SCROLL_SPEED = 10;

static const float STEPMOVE = 50.f;

static const int FPS_LIMIT = 14;

void checkViewLimits(View &mapView, View &minimap, float yMax, float xMax);

using namespace sf;
using namespace gui_constants;
int main()
{
    Thread thread(&SocketGUI::getInstance);//Init Connection
    thread.launch();

    //cout<<"Press Enter to begin..."<<endl;
    //cin.ignore();
    Map* mapa = Map::getInstance();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    VideoMode video = VideoMode::getDesktopMode();
    video.height *=0.7;
    video.width *=0.7;
    RenderWindow window(video, WINDOW_NAME, sf::Style::Default, settings);
    window.setFramerateLimit(FPS_LIMIT);
    unsigned int heightScreen = window.getSize().y;
    unsigned int widthScreen = window.getSize().x;
    //Original View
    sf::View fixed = window.getView();
    sf::View mapView(Vector2f(mapa->width*mapa->tileWidth/2,mapa->height*mapa->tileHeight/2), Vector2f(widthScreen*2,heightScreen*2));
    //Minimap
    unsigned int size = 300;
    sf::View minimap(Vector2f(mapa->width*mapa->tileWidth/2,mapa->height*mapa->tileHeight/2),Vector2f(static_cast<float>(size), static_cast<float>(window.getSize().y*size/window.getSize().x)));
    minimap.setViewport(sf::FloatRect(1.f-static_cast<float>(minimap.getSize().x)/window.getSize().x-0.02f, 1.f-static_cast<float>(minimap.getSize().y)/window.getSize().y-0.02f, static_cast<float>(minimap.getSize().x)/window.getSize().x, static_cast<float>(minimap.getSize().y)/window.getSize().y));
    minimap.zoom(12.f);
    mapView.setViewport(FloatRect(0.0f,0.0f,1.0f,1.0f));
    RenderTexture mapText;
    if(!mapText.create(mapa->getHeight()*mapa->getTileHeight(),mapa->getWidth()*mapa->getTileWidth())) abort;
    int lengthSlider = 100;
    Slider slider(Vector2f(widthScreen*0.5-lengthSlider, heightScreen*0.02), lengthSlider);

    float yMax = mapa->getHeight()*mapa->getTileHeight();
    float xMax = mapa->getWidth()*mapa->getTileWidth();
    while (window.isOpen())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            slider.move(Mouse::getPosition(window));
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                thread.terminate();
            }

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

                checkViewLimits(mapView, minimap, yMax, xMax);
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

                else if(event.key.code == sf::Keyboard::I)
                {
                    mapView.zoom(0.5f);
                }
                else if(event.key.code == sf::Keyboard::O)
                {
                    mapView.zoom(2.0f);
                }


                checkViewLimits(mapView,minimap, yMax, xMax);
            }
        }
        mapText.clear();
        window.clear();
        //Render mAP
        window.setView(mapView);
        mapa->renderMap(mapText);
        mapText.display();
        //Draw map and miniMap
        window.draw(Sprite(mapText.getTexture()));
        window.setView(minimap);
        window.draw(Sprite(mapText.getTexture()));
        //Draw Slider
        window.setView(fixed);
        slider.drawSlider(window);
        window.display();
    }


    return 0;
}

void checkViewLimits(View &mapView,View &minimap, float yMax, float xMax) {
    float xMin = mapView.getSize().x/2;
    float yMin = mapView.getSize().y/2;
    yMax -= mapView.getSize().y/2;
    xMax -= mapView.getSize().x/2;
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