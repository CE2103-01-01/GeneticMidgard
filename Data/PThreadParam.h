//
// Created by roberto on 02/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_PTHREADPARAM_H
#define PROJECTMIDGARDLOGIC_PTHREADPARAM_H


#include <pthread.h>

class PThreadParam {
    void* excecutioner;
    pthread_mutex_t* mutex;
    pthread_cond_t* condition;
    public:
        PThreadParam(void*, pthread_mutex_t*, pthread_cond_t*);
        ~PThreadParam();
        void* getExcecutioner();
        pthread_mutex_t* getMutex();
        pthread_cond_t* getCondition();
};


#endif //PROJECTMIDGARDLOGIC_PTHREADPARAM_H
