// *** ADDED BY HEADER FIXUP ***
#include <string>
// *** END ***
//
// Created by pablo on 20/04/15.
//

#ifndef PROJECTMIDGARD_RANDOM_H
#define PROJECTMIDGARD_RANDOM_H

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "../Data/Stack.h"
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
namespace trueRandom
{
    void init();
    int getRandom();
    int randRange(int,int);
    float randRange(float, float);


}
void *receive_numbers(void* );

#endif //PROJECTMIDGARD_RANDOM_H
