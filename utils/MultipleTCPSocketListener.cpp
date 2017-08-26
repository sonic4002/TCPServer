//
// Created by omrih on 21-Jun-17.
//


#include "MultipleTCPSocketListener.h"

using namespace npl;

MultipleTCPSocketListener::MultipleTCPSocketListener() {


}

void MultipleTCPSocketListener::add(TCPSocket* sock) {
    sockVec.push_back(sock);

}

void MultipleTCPSocketListener::remove(TCPSocket* sock) {
    vector<TCPSocket*>::iterator iter = sockVec.begin();
    vector<TCPSocket*>::iterator endIter = sockVec.end();
    for (;iter != endIter;iter++) {
        if (inet_ntoa((*iter)->get_from().sin_addr) == inet_ntoa(sock->get_from().sin_addr)){
            cout << "ITER loop to ERASE : " << inet_ntoa((*iter)->get_from().sin_addr) << endl;
            break;
        }
    }
    sockVec.erase(iter);
    cout<< "new size is " << sockVec.size() << endl;
}

void MultipleTCPSocketListener::add(vector<TCPSocket*> sockVector) {
    sockVec = sockVector;

}

TCPSocket* MultipleTCPSocketListener::listen(int timeout) {

    struct timeval tv = {timeout, 0};
    vector<TCPSocket*>::iterator iter = sockVec.begin();
    vector<TCPSocket*>::iterator endIter = sockVec.end();
    fd_set fdset;
    FD_ZERO(&fdset);
    int max_fd = 0;
    //fill the set with file descriptors
    for (;iter != endIter;iter++) {
        max_fd++;
        FD_SET((*iter)->get_fd(),&fdset);
        if ((*iter)->get_fd()>max_fd)
            max_fd = (*iter)->get_fd();
    }

    //perform the select
    int returned;
    if (timeout>0){
        returned = select(sizeof(fdset)*8, &fdset, NULL, NULL, &tv);
    }else{
        returned = select(sizeof(fdset)*8, &fdset, NULL, NULL, NULL);
    }
    if (returned) {
        for (int i = 0; i < max_fd; i++) {
            TCPSocket* tmpSocket = sockVec[i];
            if (FD_ISSET(tmpSocket->get_fd(), &fdset)) {
                return tmpSocket;
            }
        }
    }
    return NULL;
}

MultipleTCPSocketListener::~MultipleTCPSocketListener() {
    // TODO Auto-generated destructor stub
}
