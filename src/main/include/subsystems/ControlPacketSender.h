#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <thread>

class ControlPacketSender {
private:

    //constant variables for establishing connection
    const char* hostname = "team5708pi.local";
    const char* port = "5805";

    //specific network/connection variables
    int sockfd = -1;
    bool gotSockInfo = false;
    addrinfo* piSockInfo;

    bool isAlive = false;

    std::thread connectionThread;
public:
    ControlPacketSender();
    ~ControlPacketSender();

    std::string sendMsg(std::string msg);
private:
    int setupSocket();
    void handleConnection();
};

