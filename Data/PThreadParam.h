//
// Created by roberto on 02/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_PTHREADPARAM_H
#define PROJECTMIDGARDLOGIC_PTHREADPARAM_H


#include <pthread.h>

class PThreadParam {
    void* excecutioner;
    pthread_mutex_t* mutex;
    public:
        PThreadParam(void*, pthread_mutex_t*);
        ~PThreadParam();
        void* getExcecutioner();
        pthread_mutex_t* getMutex();
};


#endif //PROJECTMIDGARDLOGIC_PTHREADPARAM_H
