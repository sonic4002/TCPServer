//
// Created by omrih on 30-Jul-17.
//

#ifndef TCPCLIENTSERVERGAME_USERMANAGER_H
#define TCPCLIENTSERVERGAME_USERMANAGER_H

#include <string>
#include <iostream>
#include "../utils/File.h"
#include "../utils/TCPMessengerProtocol.h"

using namespace std;
namespace npl{
    class UserManager :public MThread{

        private:
            File * file = new File(USERS_FILE);
            TCPSocket * peer;
            Dispatcher * dispatcher;

        public:
            UserManager( TCPSocket * p, Dispatcher * d);
            void run();
            ~UserManager();
    };


}


#endif //TCPCLIENTSERVERGAME_USERMANAGER_H
