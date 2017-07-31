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
        MultipleTCPSocketListener listener;
        listener.add(peer1);
        listener.add(peer2);
        TCPSocket*peer = listener.listen(5);
        if(peer != NULL){
            int command;
            string data = "";
            TCPMessengerProtocol::readFromServer(command, data,peer);
            cout<< "BROKER read command from peer "<< command << " " << data <<endl;
            switch (command){
                case CLOSE_SESSION_WITH_PEER:
                    dispatcher->add(peer1);
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
