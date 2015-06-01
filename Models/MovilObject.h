//
// Created by roberto on 31/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_MOVILOBJECT_H
#define PROJECTMIDGARDLOGIC_MOVILOBJECT_H

#include "Subject.h"

class Subject;

class MovilObject {

    int effect;
    int object;
    bool use;
    int id;
public:
    int position_x;
    int position_y;
    bool operator ==(MovilObject);
    MovilObject(int,int,int,int,int,int);
    void applyEffect(Subject* person);
    int getId();
    int get_X_Position();
    int get_Y_Position();
    int getEffect();
    int getCharacteristic();
    Vector2D getVector();

};


#endif //PROJECTMIDGARDLOGIC_MOVILOBJECT_H
