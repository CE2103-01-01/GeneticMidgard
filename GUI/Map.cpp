//
// Created by Pablo Rodriguez Quesada on 5/1/15.
//


#include "Map.h"

Map *Map::singleton = NULL;

Map::Map() {

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
    //cout<<lastGid<<endl;
    //Terrain settings
    int pos = 0;
    for (rapidxml::xml_node<> *layer_node = root_node->first_node(LAYER_NODE); layer_node;
         layer_node = layer_node->next_sibling()) {
        terrain[pos] = static_cast<int*>(malloc(sizeof(int)*width*height));

        rapidxml::xml_node<> *data_node = layer_node->first_node(DATA_NODE);
        int i = 0;//para puntero
        for (rapidxml::xml_node<> *tile_node = data_node->first_node(TILE_NODE); tile_node;
             tile_node = tile_node->next_sibling()) {
/**
 *    if(trees==0){
                *(terrain[pos] + i) = 1;
            }else{
                int coin = rand()%300;
                switch(coin){
                    case 0:
                        *(terrain[pos] + i) = 37;
                        trees--;
                        break;
                    case 1:
                        *(terrain[pos] + i) = 36;
                        trees--;
                        break;
                    case 2:
                        *(terrain[pos] + i) = 19;
                        trees--;
                        break;
                    default:
                        *(terrain[pos] + i) = 1;
                        break;
                }
 */
            *(terrain[pos] + i) = std::atoi(tile_node->first_attribute("gid")->value());
            i++;// contador para el puntero
        }
        pos++;
    }
    //create Poblacion
    if(!texture.loadFromFile(tilesetPath)) abort();
    unsigned int personGid;
    unsigned int personAlphaGid;
    rapidxml::xml_node<> *terrain_node = root_node->first_node(TILESET_NODE)->first_node(TERRAINS)->first_node(
            TERRAIN_NODE);
    while (terrain_node)
    {
        if(!strcmp(terrain_node->first_attribute(NAME)->value(), PERSONA_TERRAIN))
            personGid = std::atoi(terrain_node->first_attribute(TILE_NODE)->value())+1;// Ojo el mas 1 para pasar de id a gid
        else if(!strcmp(terrain_node->first_attribute(NAME)->value(), ALPHA_PERSON))
            personAlphaGid = std::atoi(terrain_node->first_attribute(TILE_NODE)->value())+1;// Ojo el mas 1 para pasar de id a gid
        terrain_node = terrain_node->next_sibling();
    }
    Texture texturePerson;
    if (!texturePerson.loadFromFile(tilesetPath,getTileRect(personGid))) abort();
    Texture texturePersonLayer;
    if (!texturePersonLayer.loadFromFile(tilesetPath,getTileRect(personAlphaGid))) abort();
    if(personGid==0||personAlphaGid==0) cerr<<"Error Textura de Personas no definida"<<endl;
    poblacion = new Poblacion(texturePerson,texturePersonLayer);
    needToPaint = true;
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

void Map::renderMap(RenderTarget& renderArea, const IntRect &rect) {
        int i;
        int j;
    int leftBound = rect.left/tileWidth;
    if(leftBound<0)leftBound=0;
    int topBound = rect.top/tileWidth;
    if(topBound<0)topBound=0;
    for (int layer = 0; layer < 2; ++layer) {
            int *layerData = (terrain[layer]);
            for (i = leftBound; i < rect.width/tileWidth+1 && i<width ; ++i) {
                for (j = topBound; j < rect.height/tileHeight+1 && j < height; ++j) {

                    int gid = *(layerData + i + (width * j));
                    if (!gid) continue;
                    Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setTextureRect(getTileRect(gid));
                    sprite.setPosition(sf::Vector2f(tileWidth * i, tileHeight * j));
                    renderArea.draw(sprite);
                }
            }
        }

    poblacion->drawPoblacion(renderArea, IntRect(leftBound, topBound,i-leftBound,j-topBound));
}

    IntRect Map::getTileRect(unsigned int i) {
    i--;//start on 0 not in 1

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

Texture Map::getTexture() {
    return texture;
}

Map *Map::getInstance() {
    if(!singleton)
    {
        singleton = new Map();
    }
    return singleton;
}

Poblacion *Map::getPoblacion() {
    return poblacion;
}
