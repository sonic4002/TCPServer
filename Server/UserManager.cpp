//
// Created by omrih on 30-Jul-17.
//

#include "UserManager.h"
#include "../utils/TCPSocket.h"
#include "../Server/Dispatcher.h"

using namespace npl;

UserManager::UserManager(TCPSocket * p ,  Dispatcher * d){
    this->peer = p;
    this->dispatcher = d;
}


UserManager::run(){
    int cmd;
    string data;
    TCPMessengerProtocol::readFromServer(&cmd , &data , this->peer);
    switch (cmd){
        case 1:
            cout << "hello 1" << endl;
            break;
        case 2:
            cout << "hello 2" << endl;
            break;
    }
}
