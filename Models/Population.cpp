//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"
Population::Population(int size, char type) {
    populationType = static_cast<char*>(malloc(sizeof(char)));
    *populationType = type;
    people = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    new(people) Tree<Subject>(TREE_SIZE);
    for(int i = 0; i<size,i++){
        Subject newIndividual = new Subject();
        //generar el invididuo
        people.add(newIndividual);

    }

}
Population::~Population() {

}
Subject Population::getIndividual(int position) {
    if(position<people.len()){
        return people.get(position);
    }
}
Subject Population::getFittest() {

}
int Population::getPopulationSize() {
    return people.len();
}
std::string Population::getPopulationType() {
    return populationType;
}
