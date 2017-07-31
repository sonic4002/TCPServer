//
// Created by omrih on 30-Jul-17.
//

#include "UserManager.h"


using namespace npl;
using namespace std;

UserManager::UserManager(TCPSocket * p ,  Dispatcher * d){
    this->peer = p;
    this->dispatcher = d;
}


void UserManager::run(){
    int cmd;
    string data;
    bool flag = true;
    while (flag){
        TCPMessengerProtocol::readFromServer(cmd , data , this->peer);
        switch (stoi(data)){
            case 1:
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"what is your username?",peer);
                TCPMessengerProtocol::readFromServer(cmd , data , this->peer);
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"what is your password?",peer);
                TCPMessengerProtocol::readFromServer(cmd , data , this->peer);
                break;
            case 2:
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"new user name:",peer);
                TCPMessengerProtocol::readFromServer(cmd , data , this->peer);
                file->write(data);
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"new password:",peer);
                TCPMessengerProtocol::readFromServer(cmd , data , this->peer);
                file->write(" " + data + " 0\n");
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"thank you for registration",peer);
                dispatcher->add(peer);
                flag = false;
                break;
        }
    }
}

UserManager::~UserManager() {}
