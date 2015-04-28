//
// Created by Pablo Rodriguez Quesada on 4/26/15.
//


#include <pm.h>
#include "Terrain.h"

using namespace std;
int Terrain::width = 0;
int Terrain::height = 0;
int *Terrain::array = 0;

void Terrain::initArray() {
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( constants::MAP_FILE );
    doc.parse<0>( file.data() );
    //get root node
    root_node = doc.first_node(MAP_NODE);
    rapidxml::xml_node<>* layer_node = root_node->first_node(LAYER_NODE);
    layer_node = layer_node->next_sibling(LAYER_NODE);//Obtener los objetos
    rapidxml::xml_node<>* data_node = layer_node->first_node(DATA_NODE);
    width = std::atoi( layer_node->first_attribute(WIDTH)->value() );
    height = std::atoi( layer_node->first_attribute(HEIGHT)->value() );
    array = static_cast<int*>(malloc(sizeof(int)*width*height));

    int i=0;//para puntero
    for( rapidxml::xml_node<>* tile_node = data_node->first_node(TILE_NODE);
         tile_node;
         tile_node = tile_node->next_sibling() )
    {
        *(array+i)=std::atoi( tile_node->first_attribute( "gid" )->value() );
        i++;// contador para el puntero
    }
}

void Terrain::printArray() {
    for (int i = 1; i < width * height+1; ++i)
    {
        cout<<*(array+i)<<"|";
        if(i%width==0)cout<<endl;
    }
}

DoubleList<Point> Terrain::neighborNodes(Point point) {
    DoubleList<Point> neighbors = DoubleList<Point>();
    uint8_t x = point.getX();
    uint8_t y = point.getY();
    for (int i = -1; i < 2; ++i) {
        int newX = x+i;
        if (newX <0||newX>width) continue;
        for (int j = -1; j < 2; ++j) {
            int newY = y+i;
            if(newY <0|| newY >height) continue;
            neighbors.append(Point(newX,newY));
        } 
    }
    return neighbors;
};

DoubleList<Point> Terrain::AStar(Point start, Point goal) {
    DoubleList<Point> closedSet = DoubleList<Point>();
    DoubleList<Point> openSet = DoubleList<Point>(); openSet.append(start);
    DoubleList<Point> trace = DoubleList<Point>();
    start.setGScore(0); start.setFScore(heuristic(start,goal));
    Point *current;
    while(!openSet.empty())
    {
        Point* current = Point::lowestFScore(openSet);
        if (goal == current) return trace;
        openSet.deleteNodeByData(*current);//TODO- check if by number
        closedSet.append(current);
        DoubleListIterator<Point> *neighborIter = neighborNodes(*current).getIterator();
        while (neighborIter->exists())
        {
            Point *neighbor = neighborIter->next();
            if (closedSet.has(*neighbor))continue;
            
        }
    }
    return trace;
}

inline int Terrain::heuristic(Point start, Point goal) {
    return abs(start.getX() - goal.getX()) + abs(start.getY() - goal.getY());
}



//Point
//Constructors
Point::Point(uint8_t pX, uint8_t pY) {
    x,y = pX,pY;
}

Point::Point(uint8_t pX, uint8_t pY, uint8_t pfScore) {
    x,y,fScore = pX,pY,pfScore;
}


// Getters and Setters
uint8_t Point::getX() {
    return x;
}

uint8_t Point::getY() {
    return y;
}

uint8_t Point::getFScore() {
    return fScore;
}

uint8_t Point::getGScore() {
    return gScore;
}

void Point::setX(uint8_t pX) {
    x = pX;
}

void Point::setY(uint8_t pY) {
    y = pY;
}

void Point::setFScore(uint8_t pScore) {
    fScore = pScore;
}

void Point::setGScore(uint8_t pScore) {
    gScore = pScore;
}

Point *Point::lowestFScore(DoubleList<Point> list) {
    DoubleListIterator<Point>* iter = list.getIterator();
    Point* lowest;
    if (iter->exists()) lowest = iter->next();
    while(iter->exists())
    {
        Point* actual = iter->next();
        if (actual->getFScore()<lowest->getFScore()) lowest = actual;
    }
    return lowest;
}
//Operators
bool Point::operator==(Point point) {
    return (point.getX()==x && point.getY() == y);
}

bool Point::operator==(Point *point) {
    return (point->getX()==x && point->getY() == y);
}


