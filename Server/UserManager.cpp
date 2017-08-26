//
// Created by omrih on 30-Jul-17.
//

#include "UserManager.h"


using namespace npl;
using namespace std;


UserManager::UserManager(TCPSocket * p ,  Dispatcher * d , File * f){
    this->peer = p;
    this->dispatcher = d;
    this->file = f;
}


void UserManager::run(){
    std::hash<std::string> hash;
    int cmd;
    string msg,user,pass,hashed_pass;
    bool flag = true;
    TCPMessengerProtocol::readFromServer(cmd , msg , this->peer);
    while (flag){
        switch (stoi(msg)){
            case 1:
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"what is your username?",peer);
                TCPMessengerProtocol::readFromServer(cmd , user , this->peer);
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"what is your password?",peer);
                TCPMessengerProtocol::readFromServer(cmd , pass , this->peer);
                pass = hash(pass);
                if (file->find_user_and_pass(user,pass)){
                    peer->username[user.copy(peer->username , user.length(),0)] ='\0';
                    peer->setIsConnected(true);
                    TCPMessengerProtocol::sendToServer(SUCCESS,"login succeful\nW-E-L-C-O-M-E",peer);
                    dispatcher->add(peer);
                }
                else{
                    TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"wrong credentials!\ndisconnecting...",peer);
                    peer->close();
                }
                flag = false;
                break;
            case 2:
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"new user name:",peer);
                TCPMessengerProtocol::readFromServer(cmd , user , this->peer);
                TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"new password:",peer);
                TCPMessengerProtocol::readFromServer(cmd , pass , this->peer);
                pass = hash(pass);
                if (!file->find_user(user)){
                    file->write(user);
                    file->write(" " + pass + " 0\n");
                    TCPMessengerProtocol::sendToServer(SUCCESS,"thank you for registration\nW-E-L-C-O-M-E",peer);
                    peer->username[user.copy(peer->username , user.length(),0)] ='\0';
                    peer->setIsConnected(true);
                    dispatcher->add(peer);
                    flag = false;
                }
                else{
                    TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"user already exists\nretry",peer);
                    msg = '2';
                }
                break;
        }
    }
    this->~UserManager();
}

UserManager::~UserManager() {
    this->~MThread();
}
