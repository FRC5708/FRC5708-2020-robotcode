#include "subsystems/ControlPacketSender.h"

#include <cstring>
#include <iostream>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <chrono>

ControlPacketSender::ControlPacketSender() {
    connectionThread = std::thread(&ControlPacketSender::handleConnection, this);
    messagerThread = std::thread(&ControlPacketSender::handleMessages, this);
}

ControlPacketSender::~ControlPacketSender(){
    if(gotSockInfo){
        freeaddrinfo(piSockInfo);
    }
    close(sockfd);
    connectionThread.join();
    messagerThread.join();
}

int ControlPacketSender::setupSocket(){
    addrinfo hints;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = SO_REUSEADDR;
    hints.ai_protocol = 0;

    //I think this will fail if the pi isn't up
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
        std::cout << "Finished making socket" << std::endl;
        while(true){
            if(!isAlive){
                if(!(connect(sockfd, piSockInfo->ai_addr, piSockInfo->ai_addrlen) < 0)){ 
                    isAlive = true;
                    std::cout << "Connected to pi hopefully" << std::endl;
                    //TO DO: get connection message and only set alive if we receive it?
                    char responseMessage[65536];
                    int len = read(sockfd, responseMessage, sizeof(responseMessage)-1);
                    if(len <= 0){
                        isAlive = false;
                        perror("@handleConnection pi connection response");
                        std::cout << "Connection isn't actually alive" << std::endl;
                    }             
                    responseMessage[len] = '\0';
                } else {
                    perror("@handleConnection failed to connect");
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void ControlPacketSender::handleMessages(){
    while(true){
        //std::unique_lock<std::mutex> lck(mtx);
        //std::cout << "handle messages: about to wait" << std::endl;
        //cv.wait(lck);
        //std::cout << "finished waiting" << std::endl;
        //lck.unlock();
        std::cout << "Handling Message: CM: " <<  currentMessage << " size: " << messageQueue.size()<< std::endl;
        if(isAlive){
            std::cout << "Yeah, its alive" << std::endl;
            for(; currentMessage < messageQueue.size(); currentMessage++){
                std::cout << "Trying to send message: " << messageQueue[currentMessage].toSend << std::endl;
                std::optional<std::string> response = sendMsg(messageQueue[currentMessage].toSend);
                if(!(response.has_value())){
                    isAlive = false;
                    break;
                } else {
                    messageQueue[currentMessage].response = response;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

std::optional<std::string> ControlPacketSender::sendMsg(std::string msg){
    if(write(sockfd, msg.c_str(), msg.length()) < 0){
        isAlive = false;
        perror("@sendMsg write");
        return {};
    }
    //get the response
    char responseMessage[65536];
    int len = read(sockfd, responseMessage, sizeof(responseMessage)-1);
    if(len < 0){
        isAlive = false;
        perror("@sendMsg read");
        return {};
    }
    responseMessage[len] = '\0';
    std::cout << "Received PI response: \" " << responseMessage << "\"" << std::endl;
    return std::string(responseMessage);
}

int ControlPacketSender::queueMsg(std::string msg){
    std::cout << "Queueing message" << std::endl;
    messageQueue.push_back(ControlPacket(msg));
    //std::unique_lock<std::mutex> lck(mtx);
    std::cout << "triggering handle message" << std::endl;
    //cv.notify_all();
    //lck.unlock();
    std::cout << "finished notification" << std::endl;
    return messageQueue.size()-1; 
}

std::optional<std::string> ControlPacketSender::getResponse(unsigned int msgId){
    if(msgId < messageQueue.size()){
        return messageQueue[msgId].response;
    } else {
        return {};
    }
}
