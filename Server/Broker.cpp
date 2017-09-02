//
// Created by omrih on 21-Jun-17.
//
#include "Broker.h"
#include "Dispatcher.h"
#include "../utils/TCPMessengerProtocol.h"
using namespace npl ;

Broker::Broker() {
    running = false;
}

void Broker:: add(TCPSocket* peer1,TCPSocket* peer2 , Dispatcher * dispatcher){
    cout << "adding to broker" << endl;
    this->peer1 = peer1;
    this->peer2 = peer2;
    this->dispatcher = dispatcher;

    cout<< "FROM ADDRESS : " << inet_ntoa(peer1->get_from().sin_addr) << " FROM PORT : " << peer1->get_from().sin_port << endl;
    cout<< "FROM ADDRESS : " << inet_ntoa(peer2->get_from().sin_addr) << " FROM PORT : " << peer2->get_from().sin_port << endl;
    if(!running){
        running = true;
        start();
    }

}

void Broker:: run(){
    while(running){
        cout << "running in broker1" << endl;
        MultipleTCPSocketListener listener;
        listener.add(peer1);
        listener.add(peer2);
        TCPSocket*peer = listener.listen(5);
        if(peer != NULL){
            cout << "running in broker2" << endl;
            int command;
            string data = "";
            TCPMessengerProtocol::readFromServer(command, data,peer);
            cout<< "BROKER read command from peer "<< command << " " << data <<endl;
            switch (command){
                case SESSION_REFUSED:
                    cout << "peer1- username " << peer1->username << "back to dispatcher *******" << endl;
                    TCPMessengerProtocol::sendToServer(SESSION_REFUSED,"",peer);
                    dispatcher->add(peer1);
                    cout << "peer2- username " << peer2->username << "back to dispatcher *******" << endl;
                    dispatcher->add(peer2);
                    cout<<"peers returned to the dispatcher" << endl;
                    close();
                    break;
                case SEND_MSG_TO_PEER:
                    if (peer == peer1){
                        TCPMessengerProtocol::sendToServer(command , data , peer2);
                    }
                    else{
                        TCPMessengerProtocol::sendToServer(command , data , peer1);
                    }
                    break;
                case GAME_OVER:
                    dispatcher->add(peer1);
                    dispatcher->add(peer2);
                    cout<<"peers returned to the dispatcher" << endl;
                    close();
                    break;
            }
        }
    }
}



void Broker:: close(){
    running = false;
    cout<<"Broker closing connection" <<endl;
    delete(this);
}


Broker::~Broker() {
    // TODO Auto-generated destructor stub
    cout<<"Broker IS DEAD;" <<endl;
}
