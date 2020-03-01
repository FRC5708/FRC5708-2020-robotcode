#include "subsystems/VisionReceiver.h"
#include <iostream>
#include <streambuf>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>


constexpr char VISION_PORT[] = "5808";

VisionReceiver* visionReceiverInstance=nullptr;

VisionReceiver::VisionReceiver() {
	setupSocket();
	assert(visionReceiverInstance==nullptr); //We should only have one vision receiver.
	visionReceiverInstance=this;
}
VisionReceiver* VisionReceiver::getVisionReceiver(){
	assert(visionReceiverInstance!=nullptr);
	return visionReceiverInstance;
}

void VisionReceiver::setupSocket() {
	
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;   /* For wildcard IP address */

	struct addrinfo *result;

	int error = getaddrinfo(nullptr, VISION_PORT, &hints, &result);
	if (error != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
	}

	for (struct addrinfo *rp = result; rp != NULL; rp = rp->ai_next) {
               sockfd = socket(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol);
        if (sockfd != -1) {

			if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0) break;
			else {
				perror("failed to bind to vision socket");
				close(sockfd);
				sockfd = -1;
			}
		}
	}
	freeaddrinfo(result);

	if (sockfd == -1) {
		std::cout << "could not connect to vision socket" << std::endl;
	}
}

void VisionReceiver::Periodic() {
	++dataAge;
	
	//std::cout << "VisionReciever::Periodic : " << std::endl;
	
	std::vector<TargetData> readTapes;
	
	std::stringbuf visionDataStreamBuf;
	std::iostream visionDataStream(&visionDataStreamBuf);

	char buf[66537];
	ssize_t recieveSize = recvfrom(sockfd, buf, sizeof(buf) - 1, 
	MSG_DONTWAIT, (struct sockaddr *) &clientAddr, &clientAddrLen);
	if (recieveSize > 0) {
		clientAddrExists = true;

		buf[recieveSize] = '\0';
		visionDataStream << buf;

		std::string line;
		while (std::getline(visionDataStream, line)) {
			if (line[0] == '#') {
				std::cout << line << std::endl;
				double distance, tapeAngle, robotAngle;
				sscanf(line.c_str(), "# distance=%lf tapeAngle=%lf robotAngle=%lf",
				&distance, &tapeAngle, &robotAngle);
				
				TargetData data = TargetData(units::inch_t(distance), units::radian_t(tapeAngle), units::radian_t(robotAngle));
				readTapes.push_back(data);
			}
			else if(line[0] == '@') {
				sscanf(line.c_str(), "@%d", &processingTime);
			}
			else {
				perror("Vision data parse error, invalid header");
				goto CLEAR;
			}
		}
	}
	else if (recieveSize < 0 && errno != EWOULDBLOCK) {
		perror("vision data recieve error");
		return;
	}
	// else do nothing
	
	if (readTapes.size() != 0) {
		dataAge = 0;
		
		// Milliseconds. Network, camera, etc.
		constexpr double extraLatency = 20;

		if(processingTime + extraLatency > 1000){ //If data is really old
			goto CLEAR;
		}
        
		//TO DO: use John's odometry to place the target into odometry space
		//TO DO: decide if the received target makes sense in odometry space
		bestTarget = PossibleTarget(readTapes[0]);
		newData = true;
	} else {
		//std::cout << "No data found" << std::endl;
	}
	CLEAR:
	readTapes.clear();
	//std::cout << "@CLEAR:" << std::endl;
	//More stuff here?
}