//
// Created by Pablo Rodriguez Quesada on 4/26/15.
//

#ifndef PROJECTMIDGARD_TERRAIN_H
#define PROJECTMIDGARD_TERRAIN_H

#define RANGO_DEL_PRIMER_INTENTO 6

static char const *const MAP_NODE = "map";
static char const *const LAYER_NODE = "layer";
static char const *const HEIGHT = "height";
static char const *const WIDTH = "width";
static char const *const DATA_NODE = "data";
static char const *const TILE_NODE = "tile";

#include <math.h>
#include <iomanip>
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"
#include "../Constants.h"
#include "../Data/PriorityQueue.h"
#include "../Data/DoubleList.h"

class Vector2D
{
public:
    Vector2D(const Vector2D&);
    Vector2D(int, int);
    int x;
    int y;
};
class Terrain {
public:
    static int width;
    static int height;
    static int *map;
    static void initArray();
    static int getFreeSpaces();
    static void printArray();
    static DoubleList<Vector2D> findPathAS(const Vector2D &start, const Vector2D &finish);
    static Vector2D getRandomFreePosition();
    static Vector2D getRandomFreePositionNear(Vector2D);
    static int get(Vector2D);
    static int get(int,int);
    static void set(Vector2D, int);
    static void set(int, int, int);

};

class NodeAS {
private:
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // 1 / realPriority
public:
    NodeAS(int xPos, int yPos, int level, int priority);
    bool operator<(NodeAS node);
    void updatePriority(const int & xDest, const int & yDest);
    void nextLevel(const int & i);
    int const &estimate(const int & xDest, const int & yDest) const;
    int getxPos() const;
    int getyPos() const;
    int getLevel() const;
    int getPriority() const;


};

#endif //PROJECTMIDGARD_TERRAIN_H
