//
// Created by omrih on 21-Jun-17.
//



#include "TCPMessengerServer.h"
#include "UserManager.h"

using namespace npl ;

TCPMessengerServer::TCPMessengerServer() {
    sock = new TCPSocket(3346);
    dispacher = new Dispatcher();
    start();
}

void TCPMessengerServer::listpeer(){
    dispacher->listPeer();
}
void TCPMessengerServer::exit(){
    sock->close();
    waitForThread();
    dispacher->close();
}
void TCPMessengerServer::run(){

    UserManager * um;
    file  = new File(USERS_FILE);
    while(true){
        TCPSocket* peer = sock->listenAndAccept();
        cout << "is connected in server::run" << peer ->isIsConnected() << endl;
        if (peer == NULL){
            break;
        }
        TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER,"send 1 for login\nsend 2 to register",peer);

        um = new UserManager(peer , dispacher , file);
        um->start();

//        dispacher->add(peer);

    }

}

TCPMessengerServer::~TCPMessengerServer() {
    // TODO Auto-generated destructor stub
}
