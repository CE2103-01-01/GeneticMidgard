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

static char const *const TILE_NODE = "title";
#include <iostream>
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"
#include "../Constants.h"
#include "../Data/DoubleList.h"
class Point;
class Terrain {
public:
    static int width;
    static int height;
    static int *array ;
    static void initArray();
    static void printArray();
    static inline int heuristic(Point start, Point goal);
    static DoubleList<Point> AStar(Point start, Point goal);
    static DoubleList<Point> neighborNodes(Point);
};

class Point
{
private:
    uint8_t x;
    uint8_t y;
    uint8_t fScore;
    uint8_t gScore;
public:
    Point(uint8_t, uint8_t);
    Point(uint8_t, uint8_t, uint8_t);
    bool operator==(Point);
    bool operator==(Point*);
    static Point* lowestFScore(DoubleList<Point>);
    static Point* lowestGScore(DoubleList<Point>);
    uint8_t getX();
    uint8_t getY();
    uint8_t getFScore();
    uint8_t getGScore();
    void setX(uint8_t pX);
    void setY(uint8_t pY);
    void setFScore(uint8_t pScore);
    void setGScore(uint8_t pScore);
    
};

#endif //PROJECTMIDGARD_TERRAIN_H
