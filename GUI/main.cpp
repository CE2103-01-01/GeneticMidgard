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

IntRect getRenderArea();
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
    minimap.zoom(14.f);
    mapView.setViewport(FloatRect(0.0f,0.0f,1.0f,1.0f));
    RenderTexture mapText;
    if(!mapText.create(mapa->getWidth()*mapa->getTileWidth(), mapa->getHeight()*mapa->getTileHeight())) abort;
    int lengthSlider = 100;
    slider = Slider(Vector2f(widthScreen*0.5-lengthSlider, heightScreen*0.02), lengthSlider);

    yMax = mapa->getHeight()*mapa->getTileHeight();
    xMax = mapa->getWidth()*mapa->getTileWidth();
    while (window.isOpen())
    {
        ManageEvents(socketThread,window);
        //std::cout << "Need to Paint? " << std::endl;
        if(!(Map::getInstance()->needToPaint)) continue;
        (Map::getInstance()->needToPaint) = false;
        //std::cout << "Painting " << std::endl;
        mapText.clear();
        window.clear();
        //Render map
        window.setView(mapView);
        mapa->renderMap(mapText, getRenderArea());
        mapText.display();
        //Draw map and miniMap
        Sprite mapSprite = Sprite(mapText.getTexture());
        window.draw(mapSprite);
        window.setView(minimap);
        mapSprite.setColor(Color(235,235,255,245));
        window.draw(mapSprite);
        //Draw Slider
        window.setView(fixed);
        slider.drawSlider(window);
        window.display();
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
    (Map::getInstance()->needToPaint) = true;
}

IntRect getRenderArea()
{   //MiniMap Limits
    int minX = minimap.getCenter().x-minimap.getSize().x/2;
    int minY = minimap.getCenter().y-minimap.getSize().y/2;
    int maxX = minX + minimap.getSize().x;
    int maxY = minY + minimap.getSize().y;
    //Map Limits
    int minXMap = mapView.getCenter().x-mapView.getSize().x/2;
    int minYMap = mapView.getCenter().y-mapView.getSize().y/2;
    int maxXMap = minXMap + mapView.getSize().x;
    int maxYMap = minYMap + mapView.getSize().y;
    if(minXMap<minX)minX = minXMap;
    if(minYMap<minY)minY = minYMap;
    if(maxXMap>maxX)maxX = maxXMap;
    if(maxYMap>maxY)maxY = maxYMap;
    return IntRect(minX,minY,maxX,maxY);
}

void ManageEvents(Thread &socketThread, RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        (Map::getInstance()->needToPaint) = true;
        const Vector2i &position = Mouse::getPosition(window);
            if (!slider.move(position))
            {
                window.setView(mapView);

                Map::getInstance()->getPoblacion()->clickOnPerson(window.mapPixelToCoords(position));
            }


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
            (Map::getInstance()->needToPaint) = true;
        }

        else if (event.type == Event::MouseWheelMoved) {
            (Map::getInstance()->needToPaint) = true;
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
            (Map::getInstance()->needToPaint) = true;
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
                mapView.zoom(0.8f);
                checkViewLimits();
            }
            else if(event.key.code == Keyboard::O)
            {
                mapView.zoom(1.25f);
                if (mapView.getSize().x>xMax) mapView.setSize(xMax,yMax);
                checkViewLimits();
            }

        }
    }

}