//
// Created by Pablo Rodriguez Quesada on 4/26/15.
//

#ifndef PROJECTMIDGARD_TERRAIN_H
#define PROJECTMIDGARD_TERRAIN_H


static char const *const MAP_NODE = "map";

static char const *const LAYER_NODE = "layer";

static char const *const HEIGHT = "height";

static char const *const WIDTH = "width";

static char const *const DATA_NODE = "data";

static char const *const TILE_NODE = "tile";
#include <iostream>
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"
#include "../Constants.h"

class Terrain {
public:
    static int width;
    static int height;
    static int *array ;
    static void initArray();
    static void printArray();
};


#endif //PROJECTMIDGARD_TERRAIN_H
