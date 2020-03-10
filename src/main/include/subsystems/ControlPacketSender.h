#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <thread>
#include <optional>
#include <vector>
#include <mutex>
#include <condition_variable>

struct ControlPacket {
    ControlPacket(std::string _toSend)
     : toSend(_toSend), response() {};
    std::string toSend;
    std::optional<std::string> response;
};

class ControlPacketSender {
private:

    //constant variables for establishing connection
    const char* hostname = "team5708pi.local";
    const char* port = "5805";

    //specific network/connection variables
    int sockfd = -1;
    bool gotSockInfo = false;
    addrinfo* piSockInfo;

    volatile bool isAlive = false;

    //messagerThread vars
    unsigned int currentMessage = 0;
    std::vector<ControlPacket> messageQueue;
    //inter-thread(main & messager) vars
    std::mutex mtx;
    std::condition_variable cv;

    //threads
    std::thread connectionThread;
    std::thread messagerThread;
public:
    ControlPacketSender();
    ~ControlPacketSender();

    int queueMsg(std::string msg);
    std::optional<std::string> getResponse(unsigned int msgId);
private:
    int getPiInfo();
    int makeSocket();
    void handleConnection();
    void handleMessages();

    std::optional<std::string> sendMsg(std::string msg);
};

