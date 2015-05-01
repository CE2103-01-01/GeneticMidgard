//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"
Population::Population(int size, char type) {
    populationType = static_cast<char*>(malloc(sizeof(char)));
    *populationType = type;
    people = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    new(people) Tree<Subject>(TREE_SIZE);

}
Population::~Population() {

}
Subject Population::getIndividual(int position) {

}
int Population::getPopulationSize() {

}
std::string Population::getPopulationType() {

}
