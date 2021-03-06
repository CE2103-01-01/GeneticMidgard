//
// Created by Pablo Rodriguez Quesada on 4/26/15.
//





#include "Terrain.h"
#include "../Interface/Random.h"


using namespace std;
int Terrain::width = 0;
int Terrain::height = 0;
int *Terrain::map = 0;
pthread_mutex_t Terrain::mutexMap = PTHREAD_MUTEX_INITIALIZER;
/*
 * Se usa este metodo para cargar el xml a memoria
 */
void Terrain::initArray() {
    pthread_mutex_lock(&mutexMap);
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
    pthread_mutex_unlock(&mutexMap);
}
/*
 * Visualiza el mapa
 */
void Terrain::printArray() {
    pthread_mutex_lock(&mutexMap);
    int* mapArray = map -1;
    for (int i = 1; i < width * height+1; ++i)
    {
        const char separator    = ' ';
        const int numWidth      = 6;
        cout << left << setw(numWidth) << setfill(separator) <<*(mapArray +i);
        //if(*(map+i)!=0)cout<<i%80<<","<<i/80<<endl;print objects
        if(i%width==0)cout<<endl;
    }
    pthread_mutex_unlock(&mutexMap);
}
/*
 * Algoritmo A* para paths
 */


Stack<Vector2D> Terrain::findPathAS(const Vector2D &start, const Vector2D &finish) {
    int closed_Nodes_map[width][height]; // map of closed (tried-out) Nodes
    int open_Nodes_map[width][height]; // map of open (not-yet-tried) Nodes
    int dir_map[width][height]; // map of directions
    const int dir=4; // number of possible directions to go at any position
    const int dx[dir]={1, 0, -1, 0};
    const int dy[dir]={0, 1, 0, -1};

    PriorityQueue<NodeAS> priorityQueue[2]; // list of open (not-yet-tried) Nodes
    priorityQueue[0] = PriorityQueue<NodeAS>();
    priorityQueue[1] = PriorityQueue<NodeAS>();
    int pqi; // pq index
    NodeAS* n0;
    NodeAS* m0;
    int dirOfMov, j, x, y, xdx, ydy;
    pqi=0;//index priority queue

    // reset the NodeAS maps
    for(y=0;y< height;y++)
    {
        for(x=0;x< width;x++)
        {
            closed_Nodes_map[x][y]=0;
            open_Nodes_map[x][y]=0;
        }
    }
    pthread_mutex_lock(&mutexMap);
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
        if(x==finish.x && y==finish.y)
        {
            Stack<Vector2D> path = Stack<Vector2D>();
            while(!(x==start.x && y==start.y))
            {
                path.push(Vector2D (x,y));
                j=dir_map[x][y];
                x+=dx[j];
                y+=dy[j];


            }

            // garbage collection
            delete n0;
            // empty the leftover Nodes
            while(!priorityQueue[pqi].empty()) priorityQueue[pqi].pop();
            pthread_mutex_unlock(&mutexMap);
            return path;
        }

        // generate moves (child Nodes) in all possible directions
        for(dirOfMov =0; dirOfMov <dir; dirOfMov++)
        {
            xdx=x+dx[dirOfMov]; ydy=y+dy[dirOfMov];

            if(!(xdx<0 || xdx> width -1 || ydy<0 || ydy> height -1 || *(map+xdx+(ydy*width))!=0
                 || closed_Nodes_map[xdx][ydy]==1))
            {
                // generate a child NodeAS
                m0=new NodeAS( xdx, ydy, n0->getLevel(),
                             n0->getPriority());
                m0->nextLevel(dirOfMov);
                m0->updatePriority(finish.x, finish.y);

                // if it is not in the open list then add into that

                if(open_Nodes_map[xdx][ydy]==0)
                {
                    open_Nodes_map[xdx][ydy]=m0->getPriority();
                    priorityQueue[pqi].push(*m0);
                    delete m0;
                    // mark its parent NodeAS direction
                    dir_map[xdx][ydy]=(dirOfMov +dir/2)%dir;
                    //Converts direction to opossite to return
                }
                else if(open_Nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_Nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(dirOfMov +dir/2)%dir;

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
                    delete m0;
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    pthread_mutex_unlock(&mutexMap);
    return Stack<Vector2D>();


}
/*
 * Auxiliar del A* para el heuristic
 */
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
/*
 * Invierte la prioridad
 */
bool NodeAS::operator<(NodeAS node) {
    return priority > node.getPriority();
}
/*
 * Se usa para cambiar la proridad de nodos
 */
void NodeAS::updatePriority(const int &xDest, const int &yDest) {
    priority=level+estimate(xDest, yDest)*10; //A*
    //cout<< priority<<endl;
}

void NodeAS::nextLevel(const int &i) {
    level+=10;//Priority going straight
}

int NodeAS::getxPos() const {
    return xPos;
}

int NodeAS::getyPos() const {
    return yPos;
}

int NodeAS::getLevel() const {
    return level;
}

int NodeAS::getPriority() const {
    return priority;
}
/*
 * Este Metodo devuelve una posicion libere
 * se obtiene un lugar random y luego se busca cerca de la posicion
 */
Vector2D Terrain::getRandomFreePosition() {
    unsigned int x = trueRandom::randRange(0,width-1);
    unsigned int y = trueRandom::randRange(0,height-1);
    if (get(x,y)==0) return Vector2D(x,y);

    return getFreePositionNear(Vector2D(x, y));


}
/**
 * Obtener una posicion libre cerca de x lugar
 */
Vector2D Terrain::getFreePositionNear(Vector2D vector){
    while(true){
        //Tira dos numeros random que indican el offset a probar
        int randomX = rand()%POSITION_RANDOM_RANGE + 1;
        int randomY = rand()%POSITION_RANDOM_RANGE + 1;
        //Tira mas random para seleccionar si el offset es negativo o positivo
        if(rand()%2) randomX=-randomX;
        if(rand()%2) randomY=-randomY;
        randomX+=vector.x;
        randomY+=vector.y;
        //Verifica si la posicion esta vacia, de ser asi la retorna
        if(0<=randomX && randomX<width && 0<=randomY && randomY<height && get(randomX,randomY)==0){
            return Vector2D(randomX, randomY);
        }
    }
}

int Terrain::get(Vector2D vector) {
    return *(map+ vector.x+(vector.y*width));
}

int Terrain::get(int i, int j) {
    pthread_mutex_lock(&mutexMap);
    if(width<i||height<j||i<0||j<0) abort();
    int data = *(map+i+(j*width));
    pthread_mutex_unlock(&mutexMap);
    return data;
}
/**
 * Cambiar un objeto en la matriz de terreno
 */
void Terrain::set(Vector2D vector, int dato) {
    pthread_mutex_lock(&mutexMap);
    *(map+ vector.x+(vector.y*width)) = dato;
    pthread_mutex_unlock(&mutexMap);
}

void Terrain::set(int i, int j, int dato) {
    pthread_mutex_lock(&mutexMap);
    if(width<i||height<j||i<0||j<0) abort();
    *(map+i+(j*width)) = dato;
    pthread_mutex_unlock(&mutexMap);
}

Vector2D::Vector2D(const Vector2D& other) {
    x=other.x;
    y=other.y;
}

Vector2D::Vector2D(int x, int y) {
    this->x=x;
    this->y=y;
}

Vector2D::Vector2D() {
    this->x=-1;
    this->y=-1;
}
/*
 * Se usa para obtener el numero libre de espacios
 */
int Terrain::getFreeSpaces() {
    int freeSpaces = 0;
    for (int i = 0; i < width * height; ++i)
    {
        if(*(map +i)==0) freeSpaces++;

    }
    return freeSpaces;
}

bool Vector2D::operator==(Vector2D other) {
    return other.x == x   &&   other.y ==y;
}

bool Vector2D::operator!=(Vector2D other) {
    return other.x != x   ||   other.y !=y;
}

