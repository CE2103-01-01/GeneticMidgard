//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"
Population::Population(int size, std::string type) {
    populationType = type;
    people = new DoubleList();
    for(int i = 0; i<size,i++){
        Subject newIndividual = new Subject();
        //generar el invididuo
        people.add(newIndividual);

    }

}
Population::~Population() {
    delete(this);
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
