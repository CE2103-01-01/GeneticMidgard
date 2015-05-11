//
// Created by Pablo Rodriguez Quesada on 4/26/15.
//





#include "Terrain.h"
#include "../Interface/Random.h"


using namespace std;
int Terrain::width = 0;
int Terrain::height = 0;
int *Terrain::map = 0;

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
    map = static_cast<int*>(malloc(sizeof(int)*width*height));

    int i=0;//para puntero
    for( rapidxml::xml_node<>* tile_node = data_node->first_node(TILE_NODE);
         tile_node;
         tile_node = tile_node->next_sibling() )
    {
        int graphicID = std::atoi(tile_node->first_attribute( "gid" )->value());
        if(graphicID != 0)graphicID = -1;
        *(map +i) = graphicID;
        i++;// contador para el puntero
    }
};

void Terrain::printArray() {
    map--;
    for (int i = 1; i < width * height+1; ++i)
    {
        const char separator    = ' ';
        const int numWidth      = 6;
        cout << left << setw(numWidth) << setfill(separator) <<*(map +i);
        //if(*(map+i)!=0)cout<<i%80<<","<<i/80<<endl;print objects
        if(i%width==0)cout<<endl;
    }
};

DoubleList<Vector2D> Terrain::findPathAS(const Vector2D &start, const Vector2D &finish) {
    int closed_Nodes_map[width][height]; // map of closed (tried-out) Nodes
    int open_Nodes_map[width][height]; // map of open (not-yet-tried) Nodes
    int dir_map[width][height]; // map of directions
    const int dir=4; // number of possible directions to go at any position
    int dx[dir]={1, 0, -1, 0};
    int dy[dir]={0, 1, 0, -1};

    static PriorityQueue<NodeAS> priorityQueue[2]; // list of open (not-yet-tried) Nodes
    static int pqi; // pq index
    static NodeAS* n0;
    static NodeAS* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the NodeAS maps
    for(y=0;y< height;y++)
    {
        for(x=0;x< width;x++)
        {
            closed_Nodes_map[x][y]=0;
            open_Nodes_map[x][y]=0;
        }
    }

    // create the start NodeAS and push into list of open Nodes
    n0=new NodeAS(start.x, start.y, 0, 0);
    n0->updatePriority(finish.x, finish.y);
    priorityQueue[pqi].push(*n0);
    open_Nodes_map[start.x][start.y]=n0->getPriority(); // mark it on the open Nodes map
    delete n0;
    // A* search
    while(!priorityQueue[pqi].empty())
    {
        // get the current NodeAS w/ the highest priority
        // from the list of open Nodes
        NodeAS const &top = priorityQueue[pqi].top();
        n0=new NodeAS( top.getxPos(), top.getyPos(),
                     top.getLevel(), top.getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        priorityQueue[pqi].pop(); // remove the NodeAS from the open list
        open_Nodes_map[x][y]=0;
        // mark it on the closed Nodes map
        closed_Nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(finish.x, finish.y) == 0)
        if(x==finish.x && y==finish.y)
        {
            // generate the path from finish to start
            // by following the directions
            DoubleList<Vector2D> path = DoubleList<Vector2D>();
            Vector2D startmp(start.x,start.y);
            Vector2D *tmp = &startmp;
            while(!(x==start.x && y==start.y))
            {
                Vector2D step(*tmp);

                j=dir_map[x][y];
                if (j==0) step.x-=1;
                else if(j==1) step.y-=1;
                else if(j==2) step.x +=1;
                else if(j==3) step.y +=1;
                cout<<step.x<<", "<<step.y<<endl;
                path.append(step);
                x+=dx[j];
                y+=dy[j];
                tmp = &step;
            }

            // garbage collection
            delete n0;
            // empty the leftover Nodes
            while(!priorityQueue[pqi].empty()) priorityQueue[pqi].pop();
            return path;
        }

        // generate moves (child Nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx> width -1 || ydy<0 || ydy> height -1 || *(map+xdx+(ydy*width))!=0
                 || closed_Nodes_map[xdx][ydy]==1))
            {
                // generate a child NodeAS
                m0=new NodeAS( xdx, ydy, n0->getLevel(),
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(finish.x, finish.y);

                // if it is not in the open list then add into that

                if(open_Nodes_map[xdx][ydy]==0)
                {
                    open_Nodes_map[xdx][ydy]=m0->getPriority();
                    priorityQueue[pqi].push(*m0);
                    delete m0;
                    // mark its parent NodeAS direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_Nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_Nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the NodeAS
                    // by emptying one pq to the other one
                    // except the NodeAS to be replaced will be ignored
                    // and the new NodeAS will be pushed in instead
                    while(!(priorityQueue[pqi].top().getxPos()==xdx &&
                            priorityQueue[pqi].top().getyPos()==ydy))
                    {
                        priorityQueue[1-pqi].push(priorityQueue[pqi].top());
                        priorityQueue[pqi].pop();
                    }
                    priorityQueue[pqi].pop(); // remove the wanted NodeAS

                    // empty the larger size pq to the smaller one
                    if(priorityQueue[pqi].size()> priorityQueue[1-pqi].size()) pqi=1-pqi;
                    while(!priorityQueue[pqi].empty())
                    {
                        priorityQueue[1-pqi].push(priorityQueue[pqi].top());
                        priorityQueue[pqi].pop();
                    }
                    pqi=1-pqi;
                    priorityQueue[pqi].push(*m0); // add the better NodeAS instead
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return DoubleList<Vector2D>();


};

 const int &NodeAS::estimate(const int &xDest, const int &yDest) const {
    static int xd, yd, d;
    xd=xDest-xPos;
    yd=yDest-yPos;

    // Euclidian Distance
    d=static_cast<int>(sqrt(xd*xd+yd*yd));

    // Manhattan distance
    //d=abs(xd)+abs(yd);


    return(d);
}
NodeAS::NodeAS(int xPos, int yPos, int level, int priority) : xPos(xPos), yPos(yPos), level(level), priority(priority) { }

bool NodeAS::operator<(NodeAS node) {
    return priority > node.getPriority();
}

void NodeAS::updatePriority(const int &xDest, const int &yDest) {
    priority=level+estimate(xDest, yDest)*10; //A*
    //cout<< priority<<endl;
};

void NodeAS::nextLevel(const int &i) {
    level+=10;//Priority going straight
};

int NodeAS::getxPos() const {
    return xPos;
};

int NodeAS::getyPos() const {
    return yPos;
};

int NodeAS::getLevel() const {
    return level;
};

int NodeAS::getPriority() const {
    return priority;
}

Vector2D Terrain::getRandomFreePosition() {
    unsigned int x = trueRandom::randRange(0,width-1);
    unsigned int y = trueRandom::randRange(0,width-1);
    if (get(x,y)==0) return Vector2D(x,y);
    //Primer intento segun rango definido
    return getRandomFreePositionNear(Vector2D(x,y));


}

Vector2D Terrain::getRandomFreePositionNear(Vector2D vector){
    int i=1;
    int max = width;
    if (height>width)max = height;
    int x,y;
    while (i<max){
        for (int switchXY = 0; switchXY < 2; ++switchXY) {//Switch between X axis wall and Y axis walls
            for (int Wall = -i; Wall <= i; Wall += 2 * i) {// Switch Between two parallel walls
                if(switchXY ==0) x = vector.x + Wall;
                else y = vector.y + Wall;
                for (int positionThroughWall = -i; positionThroughWall < i; ++positionThroughWall) {
                    if(switchXY ==0) y = vector.y + positionThroughWall;
                    else x = vector.x+ positionThroughWall;
                    if (!(x < 0 || x >= width || y < 0 || y >= width || get(x, y) != 0)) {//Free Valid Space
                        return Vector2D(x, y);
                    }
                }
            }
        }
        i++;
    }
    std::cout << "No hay espacio disponible en la matriz" << std::endl;
    return Vector2D(-1,-1);
}

int Terrain::get(Vector2D vector) {
    return *(map+ vector.x+(vector.y*width));
}

int Terrain::get(int i, int j) {
    if(width<i||height<j||i<0||j<0) abort();
    return *(map+i+(j*width));
}

void Terrain::set(Vector2D vector, int dato) {
    *(map+ vector.x+(vector.y*width)) = dato;
}

void Terrain::set(int i, int j, int dato) {
    if(width<i||height<j||i<0||j<0) abort();
    *(map+i+(j*width)) = dato;
}
