//
// Created by Pablo Rodriguez Quesada on 5/1/15.
//

#ifndef PROJECTMIDGARDLOGIC_MAP_H
#define PROJECTMIDGARDLOGIC_MAP_H

static const char *const MAP_LOCATION = "../res/mapa.tmx";

static const char *const LAYER_NODE = "layer";

static char const *const DATA_NODE = "data";

static const char *const WIDTH_NODE = "width";

static const char *const HEIGHT_NODE = "height";

static const char *const TILEWIDTH_NODE = "tilewidth";

static const char *const TILEHEIGHT_NODE = "tileheight";

static const char *const MAP_NODE = "map";

static const char *const TILESET_NODE = "tileset";

static const char *const IMAGE_NODE = "image";

static const char *const TILE_NODE = "tile";

static const char *const TILESET_PATH = "../res/";

#include <SFML/Graphics.hpp>
#include <iosfwd>
#include <string>
#include "Constants.h"
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"
#include "../Data/DoubleList.h"
#include "Poblacion.h"

using namespace sf;
using namespace std;
using namespace gui_constants;
class Map {
private:
    int *terrain[2];
    string tilesetPath = TILESET_PATH;
    unsigned int lastGid;
    Texture texture;
    Poblacion *poblacion;
public:
    Map();
    static int width;
    static int height;
    static int tileWidth;
    static int tileHeight;
    static int tilesetWidth;
    static int tilesetHeight;
    void printArray(int* array);
    int *getTerrain(int i);
    int getTileWidth();
    int getTileHeight();
    int getTilesetWidth();
    int getTilesetHeight();
    string getTilesetPath();
    int getWidth();
    int getHeight();
    Texture getTexture();
    void renderMap(RenderTarget&);
    IntRect getTileRect(unsigned int gid);
};


#endif //PROJECTMIDGARDLOGIC_MAP_H
