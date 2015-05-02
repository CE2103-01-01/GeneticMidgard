//
// Created by Pablo Rodriguez Quesada on 5/1/15.
//

#include <iostream>
#include "Map.h"

void Map::loadTerrain() {
    rapidxml::xml_node<> *root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file(MAP_LOCATION);
    doc.parse<0>(file.data());
    //get root node
    root_node = doc.first_node(MAP_NODE);
    //Map settings
    width = std::atoi(root_node->first_attribute(WIDTH_NODE)->value());
    height = std::atoi(root_node->first_attribute(HEIGHT_NODE)->value());
    tileWidth = std::atoi(root_node->first_attribute(TILEWIDTH_NODE)->value());
    tileHeight = std::atoi(root_node->first_attribute(TILEHEIGHT_NODE)->value());
    //image config
    rapidxml::xml_node<> *image_node = root_node->first_node(TILESET_NODE)->first_node(IMAGE_NODE);
    tilesetPath += image_node->first_attribute("source")->value();
    tilesetHeight = std::atoi(image_node->first_attribute(HEIGHT_NODE)->value());
    tilesetWidth = std::atoi(image_node->first_attribute(WIDTH_NODE)->value());
    lastGid = (tilesetWidth/tileWidth)*(tilesetHeight/tileHeight);
    cout<<lastGid<<endl;
    //Terrain settings
    int pos = 0;
    for (rapidxml::xml_node<> *layer_node = root_node->first_node(LAYER_NODE); layer_node;
         layer_node = layer_node->next_sibling()) {
        terrain[pos] = static_cast<int*>(malloc(sizeof(int)*width*height));

        rapidxml::xml_node<> *data_node = layer_node->first_node(DATA_NODE);
        int i = 0;//para puntero
        for (rapidxml::xml_node<> *tile_node = data_node->first_node(TILE_NODE); tile_node;
             tile_node = tile_node->next_sibling()) {

            *(terrain[pos] + i) = std::atoi(tile_node->first_attribute("gid")->value());
            i++;// contador para el puntero

        }

        pos++;

    }



}






int Map::getTileWidth() {
    return tileWidth;
}

int Map::getTileHeight() {
    return tileHeight;
}

int Map::getTilesetWidth() {
    return tilesetWidth;
}

int Map::getTilesetHeight() {
    return tilesetHeight;
}

string Map::getTilesetPath() {
    return tilesetPath;
}

void Map::printArray(int *array) {
    array -= 1;
    for (int i = 1; i < width * height+1; ++i)//empezamos a contar en uno
    {
        cout<<*(array +i)<<"|";// Se le suma uno al inicio para compensar
        if(i%width==0)cout<<endl;
    }
}

int *Map::getTerrain(int i) {
    return terrain[i];
}

void Map::renderMap(RenderWindow *renderArea) {
        Texture texture;
        if(!texture.loadFromFile(tilesetPath)) abort();
        View theView = renderArea->getView();
        for (int layer = 0; layer < 2; ++layer) {
            int *layerData = (terrain[layer]);
            for (int i = 0; i < width; ++i) {
                //cout<<theView.getSize().y<<endl;
                for (int j = 0; j < height; ++j) {
                    int gid = *(layerData + i + (width * j));
                    if (!gid) continue;
                    //Texture texture = getTitleRect(gid);
                    sf::Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setTextureRect(getTitleRect(gid));
                    sprite.setPosition(sf::Vector2f(tileWidth * i, tileHeight * j));
                    renderArea->draw(sprite);
                }
            }
        }







}

    IntRect Map::getTitleRect(unsigned int i) {
    i--;

    int x=0;
    int y=0;

    if (i!=0)
    {
        int xnum = tilesetWidth/tileWidth;
        x = (i%xnum)*tileWidth;
        y= (i/xnum)*tileHeight;
    }

    return IntRect(x, y,tileWidth,tileHeight);

}

int Map::getHeight() {
    return height;
}

int Map::getWidth() {
    return width;
}
