//
// Created by Pablo Rodriguez Quesada on 4/26/15.
//




#include "Terrain.h"
#include "../Data/PriorityQueue.h"

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
        *(map +i)=std::atoi( tile_node->first_attribute( "gid" )->value() );
        i++;// contador para el puntero
    }
};

void Terrain::printArray() {
    for (int i = 1; i < width * height+1; ++i)
    {
        cout<<*(map +i)<<"|";
        //if(*(map+i)!=0)cout<<i%80<<","<<i/80<<endl;print objects
        if(i%width==0)cout<<endl;
    }
};

void Terrain::findPathAS(const int &xStart, const int &yStart, const int &xFinish, const int &yFinish) {
    int closed_Nodes_map[width][height]; // map of closed (tried-out) Nodes
    int open_Nodes_map[width][height]; // map of open (not-yet-tried) Nodes
    int dir_map[width][height]; // map of directions
    const int dir=8; // number of possible directions to go at any position
    static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
    static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

    static PriorityQueue<Node> priorityQueue[2]; // list of open (not-yet-tried) Nodes
    static int pqi; // pq index
    static Node* n0;
    static Node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the Node maps
    for(y=0;y< height;y++)
    {
        for(x=0;x< width;x++)
        {
            closed_Nodes_map[x][y]=0;
            open_Nodes_map[x][y]=0;
        }
    }

    // create the start Node and push into list of open Nodes
    n0=new Node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    priorityQueue[pqi].push(*n0);
    open_Nodes_map[xStart][yStart]=n0->getPriority(); // mark it on the open Nodes map
    delete n0;
    // A* search
    while(!priorityQueue[pqi].empty())
    {
        // get the current Node w/ the highest priority
        // from the list of open Nodes
        Node const &top = priorityQueue[pqi].top();
        n0=new Node( top.getxPos(), top.getyPos(),
                     top.getLevel(), top.getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        priorityQueue[pqi].pop(); // remove the Node from the open list
        open_Nodes_map[x][y]=0;
        // mark it on the closed Nodes map
        closed_Nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish)
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover Nodes
            while(!priorityQueue[pqi].empty()) priorityQueue[pqi].pop();
            cout<<path<< " found";
            return;
        }

        // generate moves (child Nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx> width -1 || ydy<0 || ydy> height -1 || *(map+xdx+(ydy*width))!=0
                 || closed_Nodes_map[xdx][ydy]==1))
            {
                // generate a child Node
                m0=new Node( xdx, ydy, n0->getLevel(),
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that

                if(open_Nodes_map[xdx][ydy]==0)
                {
                    open_Nodes_map[xdx][ydy]=m0->getPriority();
                    priorityQueue[pqi].push(*m0);
                    delete m0;
                    // mark its parent Node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_Nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_Nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the Node
                    // by emptying one pq to the other one
                    // except the Node to be replaced will be ignored
                    // and the new Node will be pushed in instead
                    while(!(priorityQueue[pqi].top().getxPos()==xdx &&
                            priorityQueue[pqi].top().getyPos()==ydy))
                    {
                        priorityQueue[1-pqi].push(priorityQueue[pqi].top());
                        priorityQueue[pqi].pop();
                    }
                    priorityQueue[pqi].pop(); // remove the wanted Node

                    // empty the larger size pq to the smaller one
                    if(priorityQueue[pqi].size()> priorityQueue[1-pqi].size()) pqi=1-pqi;
                    while(!priorityQueue[pqi].empty())
                    {
                        priorityQueue[1-pqi].push(priorityQueue[pqi].top());
                        priorityQueue[pqi].pop();
                    }
                    pqi=1-pqi;
                    priorityQueue[pqi].push(*m0); // add the better Node instead
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    cout<<"no route found";


};

 const int &Node::estimate(const int &xDest, const int &yDest) const {
    static int xd, yd, d;
    xd=xDest-xPos;
    yd=yDest-yPos;

    // Euclidian Distance
    d=static_cast<int>(sqrt(xd*xd+yd*yd));

    // Manhattan distance
    //d=abs(xd)+abs(yd);


    return(d);
}
Node::Node(int xPos, int yPos, int level, int priority) : xPos(xPos), yPos(yPos), level(level), priority(priority) { }

bool Node::operator<(Node node) {
    return priority > node.getPriority();
}

void Node::updatePriority(const int &xDest, const int &yDest) {
    priority=level+estimate(xDest, yDest)*10; //A*
};

void Node::nextLevel(const int &i) {
    level+=(i%2==0?10:14);//Priority going straight
};

int Node::getxPos() const {
    return xPos;
};

int Node::getyPos() const {
    return yPos;
};

int Node::getLevel() const {
    return level;
};

int Node::getPriority() const {
    return priority;
}

