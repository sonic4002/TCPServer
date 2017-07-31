//
// Created by omrih on 21-Jun-17.
//

#ifndef UNTITLED_MTHREAD_H
#define UNTITLED_MTHREAD_H


#include <pthread.h>

namespace npl{


    class MThread{
    public:
        pthread_t threadId;

    public:
        virtual void run() = 0;
        void start();
        void waitForThread();
        virtual ~MThread();
    };

}

#endif //UNTITLED_MTHREAD_H
