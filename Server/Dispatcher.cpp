//
// Created by omrih on 21-Jun-17.
//


#include <string>
#include "Dispatcher.h"
#include "Broker.h"
using namespace npl ;
using namespace std;

Dispatcher::Dispatcher() {
    running = false;
}

void Dispatcher:: add(TCPSocket* peer){
    peers.push_back(peer);
    cout<< "new connection FROM ADDRESS : " << inet_ntoa(peer->get_from().sin_addr) << " FROM PORT : " << ntohs(peer->get_from().sin_port) << endl;
    if(!running){
        running = true;
        start();
    }

}

void Dispatcher::remove(){

}

void Dispatcher:: run(){
    vector<TCPSocket*>::iterator iter = peers.begin();
    vector<TCPSocket*>::iterator endIter = peers.end();
    Broker * broker = new Broker();
    int portInt;
    string msg = "NEW SESSION IS OPEN";
    string ip,port;
    while(true){
        if(peers.size() == 0){
            running = false;
            break;
        }
        MultipleTCPSocketListener listener;
        listener.add(peers);
        TCPSocket*peer = listener.listen(5);
        if(peer != NULL){
            int command;
            string data = "";
            TCPMessengerProtocol::readFromServer(command, data,peer);
            cout<< "read command from peer "<< inet_ntoa(peer->get_from().sin_addr) << " " << command << " " << data <<endl;
            if (peer->isIsConnected()){
                cout << "is connected in dispetcher::run " << peer->isIsConnected() << endl;
                switch (command){
                    case CLOSE_SESSION_WITH_PEER:
                        //TODO fix it to end session with broker - not disconnect from server
                        iter = peers.begin();
                        endIter = peers.end();
                        for (;iter != endIter;iter++) {
                            if (inet_ntoa((*iter)->get_from().sin_addr) == inet_ntoa((peer)->get_from().sin_addr)){
                                break;
                            }
                        }
                        cout<< "ADDRESS : " << inet_ntoa(peer->get_from().sin_addr) << " FROM PORT : " << ntohs(peer->get_from().sin_port) <<  " LEFT " << endl;

                        peer->close();
                        peers.erase(iter);
                        break;

                    case OPEN_SESSION_WITH_PEER:
                        cout<< "read command from peer "<< command << " " << data <<endl;
                        cout<< "FROM ADDRESS : " << inet_ntoa(peer->get_from().sin_addr) << " FROM PORT : " << ntohs(peer->get_from().sin_port) << endl;
                        ip = data.substr(0, data.find(":"));
                        port = data.substr(data.find(":")+1,data.length());
                        portInt = atoi(port.c_str());
                        cout << "TYR TO SEE THE PORT" << portInt << endl;
                        iter = peers.begin();
                        endIter = peers.end();
                        for (;iter != endIter;iter++) {
                            if (inet_ntoa((*iter)->get_from().sin_addr) == ip){
                                cout << "ITER loop to find : " << inet_ntoa((*iter)->get_from().sin_addr) << endl;
                                break;
                            }
                        }

                        TCPMessengerProtocol::sendToServer(command , msg , peer);
                        TCPMessengerProtocol::sendToServer(command , msg , *iter);
                        broker->add(peer, *iter , this);
                        erase_peer(peer);
                        erase_peer(*iter);
                        break;

                    case EXIT:

                        break;
                    case GET_USERS_LIST:
                        TCPMessengerProtocol::sendToServer(command , getListPeer(), peer);
                        break;
                }
            }
            else{
                if (command == EXIT){
                    iter = peers.begin();
                    endIter = peers.end();
                    for (;iter != endIter;iter++) {
                        if (inet_ntoa((*iter)->get_from().sin_addr) == inet_ntoa((peer)->get_from().sin_addr)){
                            break;
                        }
                    }
                    cout<< "ADDRESS : " << inet_ntoa(peer->get_from().sin_addr) << " FROM PORT : " << ntohs(peer->get_from().sin_port) <<  " LEFT " << endl;

                    peer->close();
                    peers.erase(iter);
                }
                cout << "client not logged in" << endl;
                TCPMessengerProtocol::sendToServer(SESSION_REFUSED , "login to server first" , peer);
            }
        }
    }

}


void Dispatcher::erase_peer(TCPSocket* sock) {
    vector<TCPSocket*>::iterator iter = peers.begin();
    vector<TCPSocket*>::iterator endIter = peers.end();
    for (;iter != endIter;iter++) {
        if (inet_ntoa((*iter)->get_from().sin_addr) == inet_ntoa(sock->get_from().sin_addr)){
            cout << "ITER loop to ERASE : " << inet_ntoa((*iter)->get_from().sin_addr) << endl;
            break;
        }
    }
    peers.erase(iter);
    cout<< "new size is " << peers.size() << endl;
}


TCPSocket * Dispatcher::FindPeer (TCPSocket * peer){
    vector<TCPSocket*>::iterator iter = peers.begin();
    vector<TCPSocket*>::iterator endIter = peers.end();
    for (;iter != endIter;iter++) {
        if ((*iter)->get_fd() == peer->get_fd()){
            return  (*iter);
        }
    }
    return NULL;
}
void Dispatcher:: listPeer(){
    vector<TCPSocket*>::iterator iter = peers.begin();
    vector<TCPSocket*>::iterator endIter = peers.end();
    for (;iter != endIter;iter++) {
        cout << (*iter)->username << endl;
    }
}

string Dispatcher:: getListPeer(){
    string str = "";
    vector<TCPSocket*>::iterator iter = peers.begin();
    vector<TCPSocket*>::iterator endIter = peers.end();
    for (;iter != endIter;iter++) {
        str.append((*iter)->username);
        str.append("\n");
    }
    str.append("\0");
    return str;
}

void Dispatcher:: close(){
    running = false;
    peers.clear();
    cout<<"Dispatcher stop join clients and close safely" <<endl;

}


Dispatcher::~Dispatcher() {
    // TODO Auto-generated destructor stub
}


