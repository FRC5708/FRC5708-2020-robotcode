#include "subsystems/ControlPacketSender.h"

#include <cstring>
#include <iostream>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

ControlPacketSender::ControlPacketSender() {
    connectionThread = std::thread(&ControlPacketSender::handleConnection, this);
}

ControlPacketSender::~ControlPacketSender(){
    if(gotSockInfo){
        freeaddrinfo(piSockInfo);
    }
    close(sockfd);
    connectionThread.join();
}

int ControlPacketSender::setupSocket(){
    addrinfo hints;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    int s = getaddrinfo(hostname, port, &hints, &piSockInfo);
    if(s != 0){
        std::cerr << "Couldn't find the PI" << std::endl;
        std::cerr << "getaddrinfo error: " << gai_strerror(s) << std::endl; 
        return -1;
    }

    sockfd = socket(piSockInfo->ai_family, piSockInfo->ai_socktype, piSockInfo->ai_protocol);
    if(sockfd == -1){
        close(sockfd);
        std::cerr << "making a socket failed" << std::endl;
        return -2; 
    }
    return 0;
}

void ControlPacketSender::handleConnection(){
    while(true){
        int e = setupSocket();
        if(e < 0){
            if(e == -2){
                //failed to create a socket (not recoverable)
                return;
            }
            //otherwise just failed to find the pi
            sleep(0.5);
            continue;
        }
        gotSockInfo = true;
        while(true){
            if(!isAlive){
                if(connect(sockfd, piSockInfo->ai_addr, piSockInfo->ai_addrlen) != -1){ 
                    isAlive = true;
                    //TO DO: get connection message and only set alive if we receive it?
                }
            }
            sleep(1);
        }
    }
}

std::string ControlPacketSender::sendMsg(std::string msg){
    if(write(sockfd, msg.c_str(), msg.length()) < 0){
        isAlive = false;
        return std::string("FAILED TO WRITE MESSAGE");
    }
    //get the response
    char responseMessage[65536];
    int len = read(sockfd, responseMessage, sizeof(responseMessage)-1);
    if(len <= 0){
        isAlive = false;
        return std::string("FAILED TO GET RESPONSE");
    }
    responseMessage[len] = '\0';
    std::cout << "Received PI response: \" " << responseMessage << "\"" << std::endl;
    return std::string(responseMessage);
}
