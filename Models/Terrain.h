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
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"
#include "../Constants.h"

class Terrain {
public:
    static int width;
    static int height;
    static int *map;
    static void initArray();
    static void printArray();
    static void findPathAS(const int & xStart, const int & yStart,
                           const int & xFinish, const int & yFinish);

};

class Node {
private:
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // 1 / realPriority
public:
    Node(int xPos, int yPos, int level, int priority);
    void updatePriority(const int & xDest, const int & yDest);
    void nextLevel(const int & i);
    int const &estimate(const int & xDest, const int & yDest) const;
    int getxPos() const;
    int getyPos() const;
    int getLevel() const;
    int getPriority() const;


};

#endif //PROJECTMIDGARD_TERRAIN_H
