//
// Created by roberto on 10/05/15.
//

#ifndef PROJECTMIDGARDLOGIC_AGEMANAGER_H
#define PROJECTMIDGARDLOGIC_AGEMANAGER_H

#include <pthread.h>
#include "PopulationManager.h"
#include "movilObjectManager.h"

#define ID_REQUEST "Ingrese el id a imprimir: "
#define SUBJECT_ID_ERROR_MESSAGE "La seccion del id ingresado correspondiente al numero de sujeto es incorrecta"
#define POPULATION_ID_ERROR_MESSAGE "La seccion del id ingresado correspondiente al numero de poblacion es incorrecta"

class AgeManager {
    pthread_mutex_t* generalMutex;
    pthread_t* managementThread;
    pthread_cond_t* condition;
    int* actualAge;
    int* years;
    void changeAge();
    void evaluateEvolution();
    bool evaluateSubject(Subject*);

    public:
        AgeManager();
        ~AgeManager();
        pthread_mutex_t* getGeneralMutex();
        pthread_cond_t* getGeneralCondition();
        void thread();
        void delete_p_thread();
        void initPopulationManager();
};

void* ageManagerThread(void*);
void* subjectPrinter(void*);

#endif //PROJECTMIDGARDLOGIC_AGEMANAGER_H
