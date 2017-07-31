//
// Created by omrih on 21-Jun-17.
//

#ifndef UNTITLED_TCPSOCKET_H
#define UNTITLED_TCPSOCKET_H

#include <netinet/in.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Socket.h"
using namespace std;

namespace npl{
    class TCPSocket:public Socket {

        bool isConnected;
    public:
        bool isIsConnected() const;

        void setIsConnected(bool isConnected);

    private:
        bool isClient;

    public:

        TCPSocket(int port);
        TCPSocket(const string &ip,int port);
        TCPSocket* listenAndAccept();
        int reply(const string& msg);
        int get_fd();
        virtual ~TCPSocket();
        struct sockaddr_in get_from();
    private:
        TCPSocket(struct sockaddr_in from,int connectSock,bool isClient);

    };
}

#endif //UNTITLED_TCPSOCKET_H
