cmake_minimum_required(VERSION 3.7)
project(Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Server/Broker.cpp
        Server/Broker.h
        Server/Dispatcher.cpp
        Server/Dispatcher.h
        Server/TCPMessengerServer.cpp
        Server/TCPMessengerServer.h
        Server/UserManager.cpp
        Server/UserManager.h
        utils/File.cpp
        utils/File.h
        utils/FileInterface.cpp
        utils/FileInterface.h
        utils/MThread.cpp
        utils/MThread.h
        utils/MultipleTCPSocketListener.cpp
        utils/MultipleTCPSocketListener.h
        utils/Socket.cpp
        utils/Socket.h
        utils/TCPMessengerProtocol.h
        utils/TCPSocket.cpp
        utils/TCPSocket.h
        server_main.cpp)

add_executable(Server ${SOURCE_FILES})