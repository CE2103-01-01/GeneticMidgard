//
// Created by roberto on 02/05/15.
//

#include "PThreadParam.h"

/**@brief: Contruye un parametro de pthread
 * @param void*: clase que ejecuta el pthread
 */
PThreadParam::PThreadParam(void* subjectParam, pthread_mutex_t* mutexParam){
    excecutioner = subjectParam;
    mutex = mutexParam;
}

/**@brief: coloca punteros en 0
 */
PThreadParam::~PThreadParam(){
    excecutioner = 0;
}

/**@brief: Accede al objeto que ejecuta el pthread
 * @return void*
 */
void* PThreadParam::getExcecutioner(){
    return excecutioner;
}

/**@brief: Accede al mutex del pthread
 * @return pthread_mutex_t*
 */
pthread_mutex_t* PThreadParam::getMutex(){
    return mutex;
};