//
// Created by Pablo Rodriguez Quesada on 4/26/15.
//


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


