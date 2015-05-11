//
// Created by pablo on 01/05/15.
//

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Map.h"
#include "../Network/SocketGUI.h"
#include "Slider.h"



View minimap;
View mapView;
Slider slider = NULL_SLIDER;
unsigned int heightScreen;
unsigned int widthScreen;
float yMax;
float xMax;


void ManageEvents(Thread &socketThread, RenderWindow &window);

using namespace sf;
using namespace gui_constants;

/*
 * Main Thread of GUI
 */
int main()
{
    Thread socketThread(&SocketGUI::getInstance);//Init Connection
    socketThread.launch();


    Map* mapa = Map::getInstance();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    VideoMode video = VideoMode::getDesktopMode();
    video.height *=0.7;
    video.width *=0.7;
    RenderWindow window(video, WINDOW_NAME, sf::Style::Default, settings);


    window.setFramerateLimit(FPS_LIMIT);
    heightScreen = window.getSize().y;
    widthScreen = window.getSize().x;
    //Original View
    View fixed = window.getView();
    mapView = View(Vector2f(mapa->width*mapa->tileWidth/2,mapa->height*mapa->tileHeight/2), Vector2f(widthScreen*2,heightScreen*2));
    //Minimap
    unsigned int size = SIZE_MINIMAP;
    minimap = View(Vector2f(mapa->width*mapa->tileWidth/2,mapa->height*mapa->tileHeight/2),Vector2f(static_cast<float>(size), static_cast<float>(window.getSize().y*size/window.getSize().x)));
    minimap.setViewport(sf::FloatRect(1.f-static_cast<float>(minimap.getSize().x)/window.getSize().x-0.02f, 1.f-static_cast<float>(minimap.getSize().y)/window.getSize().y-0.02f, static_cast<float>(minimap.getSize().x)/window.getSize().x, static_cast<float>(minimap.getSize().y)/window.getSize().y));
    minimap.zoom(12.f);
    mapView.setViewport(FloatRect(0.0f,0.0f,1.0f,1.0f));
    RenderTexture mapText;
    if(!mapText.create(mapa->getHeight()*mapa->getTileHeight(),mapa->getWidth()*mapa->getTileWidth())) abort;
    int lengthSlider = 100;
    slider = Slider(Vector2f(widthScreen*0.5-lengthSlider, heightScreen*0.02), lengthSlider);

    yMax = mapa->getHeight()*mapa->getTileHeight();
    xMax = mapa->getWidth()*mapa->getTileWidth();
    while (window.isOpen())
    {
        ManageEvents(socketThread,window);
        if(!needToPaint) continue;
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
        needToPaint = false;
    }

    return 0;
}


/*
 * Checks windows bounds
 */
void checkViewLimits() {
    float xMin = mapView.getSize().x/2;
    float yMin = mapView.getSize().y/2;
    float yMaxTemp = yMax - mapView.getSize().y/2;
    float xMaxTemp = xMax - mapView.getSize().x/2;
    if (mapView.getCenter().y > yMaxTemp)
    {
        mapView.setCenter(mapView.getCenter().x, yMaxTemp);
        minimap.setCenter(minimap.getCenter().x, yMaxTemp);
    }
    else if (mapView.getCenter().y < yMin) {
        mapView.setCenter(mapView.getCenter().x, yMin);
        minimap.setCenter(mapView.getCenter().x, yMin);
    }
    else if (mapView.getCenter().x > xMaxTemp) {
        mapView.setCenter(xMaxTemp, mapView.getCenter().y);
        minimap.setCenter(xMaxTemp, mapView.getCenter().y);
    }
    else if (mapView.getCenter().x < xMin) {
        mapView.setCenter(xMin, mapView.getCenter().y);
        minimap.setCenter(xMin, mapView.getCenter().y);
    }
    needToPaint = true;
}


void ManageEvents(Thread &socketThread, RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        slider.move(Mouse::getPosition(window));
        needToPaint = true;
    }
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed) {
            window.close();
            socketThread.terminate();
        }

            // catch the resize events
        else if (event.type == Event::Resized)
        {
            // update the view to the new size of the window
            FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(View(visibleArea));
            checkViewLimits();
            needToPaint = true;
        }

        else if (event.type == Event::MouseWheelMoved) {
            needToPaint = true;
            if (!Keyboard::isKeyPressed(Keyboard::LShift)) {
                mapView.move(0, event.mouseWheel.delta * SCROLL_SPEED);
                minimap.move(0, event.mouseWheel.delta * SCROLL_SPEED);
            }
            else {
                mapView.move(-event.mouseWheel.delta * SCROLL_SPEED, 0);
                minimap.move(-event.mouseWheel.delta * SCROLL_SPEED, 0);
            }

            checkViewLimits();
        }
        else if( event.type == Event::KeyPressed )
        {
            needToPaint = true;
            if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S){
                mapView.move(0, STEPMOVE);
                minimap.move(0, STEPMOVE);
                checkViewLimits();
            }
            else if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W){
                mapView.move(0, -STEPMOVE);
                minimap.move(0, -STEPMOVE);
                checkViewLimits();
            }
            else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D){
                mapView.move(STEPMOVE,0);
                minimap.move(STEPMOVE,0);
                checkViewLimits();
            }
            else if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A){
                mapView.move(-STEPMOVE,0);
                minimap.move(-STEPMOVE,0);
                checkViewLimits();
            }

            else if(event.key.code == Keyboard::I)
            {
                mapView.zoom(0.5f);
                checkViewLimits();
            }
            else if(event.key.code == Keyboard::O)
            {
                mapView.zoom(2.0f);
                checkViewLimits();
            }

        }
    }

}