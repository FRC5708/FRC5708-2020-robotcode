#include "subsystems/VisionReceiver.h"
#include "Robot.h"
#include <iostream>
#include <streambuf>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>


constexpr char VISION_PORT[] = "5808";

VisionReceiver::VisionReceiver() {
	setupSocket();
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

constexpr double cameraX = -11;
constexpr double cameraY = 8;
// clockwise = positive
const Degree cameraTheta = 0;

void VisionReceiver::Periodic() {
	++dataAge;

	if (ticks++ % 50 == 0) {
		sendControlHeartbeat();
	}
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
				TargetData data;
				sscanf(line.c_str(), "# distance=%lf tapeAngle=%lf robotAngle=%lf",
				&(data.tapeAngle.value), &(data.robotAngle.value));
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

// send "heartbeat" to rPi every second telling if robot is enabled or disabled
void VisionReceiver::sendControlHeartbeat() {
	std::string msg = (Robot::GetRobot()->IsEnabled() ? "ENABLE" : "DISABLE")
		+ std::string(" ")
		 + (isActivelyDriving ? "DRIVEON" : "DRIVEOFF");
		 sendControlMessage(msg.c_str());
}

void VisionReceiver::sendControlMessage(const char* message) {
	if (clientAddrExists) {
		//std::cout << "hearbeat: " << message << std::endl;
		int fd = socket(clientAddr.ss_family, SOCK_DGRAM, 0);
		if (fd < 0) perror("could not open vision control message socket");
		((sockaddr_in *) &clientAddr)->sin_port = htons(5805);
		if (sendto(fd, message, strlen(message), 0, (struct sockaddr *) &clientAddr, clientAddrLen) < 0) {
			perror("failed to send vision control message");
		}
		close(fd);
	}
}