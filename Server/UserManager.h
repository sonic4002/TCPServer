//
// Created by omrih on 30-Jul-17.
//

#ifndef TCPCLIENTSERVERGAME_USERMANAGER_H
#define TCPCLIENTSERVERGAME_USERMANAGER_H

#include <string>
#include <iostream>
#include "../utils/File.h"
#include "../utils/TCPMessengerProtocol.h"
#include "../utils/MThread.h"
#include "Dispatcher.h"
#include "../utils/File.h"

using namespace std;
namespace npl{
    class UserManager :public MThread{

        private:
            TCPSocket * peer;
            Dispatcher * dispatcher;
            File * file;
        public:
            UserManager(TCPSocket * p, Dispatcher * d , File * f);
            void run();
            ~UserManager();
    };


}


#endif //TCPCLIENTSERVERGAME_USERMANAGER_H
