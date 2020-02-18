#pragma once

#include <frc2/command/SubsystemBase.h>
#include <string>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include "Angle.h"

class VisionReceiver : public frc2::SubsystemBase {
public:
	struct TargetData {
			TargetData()
			 : distance(0), tapeAngle(Radian(0)), robotAngle(Radian(0)) {}
			TargetData(double _distance, Radian _tapeAngle, Radian _robotAngle) 
			 : distance(_distance), tapeAngle(_tapeAngle), robotAngle(_robotAngle) {}

			double distance;
			// see 2020-vision/vision.hpp for descriptions
			Radian tapeAngle, robotAngle;
	};

	struct PossibleTarget {
		PossibleTarget()
		 : hasTarget(false), target(TargetData()) {}
		PossibleTarget(TargetData t)
		 : hasTarget(true), target(t) {}

		bool hasTarget;
		TargetData target;
	};

 private:
	void setupSocket();
	void pollForData();

	void sendControlMessage(const char* message);

	int sockfd;
	struct sockaddr_storage clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	bool clientAddrExists = false;

	int ticks;

	PossibleTarget bestTarget;
 public:

	VisionReceiver();

	// Subsystem Periodic() functions are always called before command Execute() functions
	void Periodic() override;

	int processingTime; // milliseconds
	int dataAge = 999999; // ticks
	bool newData = false;

	PossibleTarget getBestTarget(){
		newData = false;
		return bestTarget;
	}

	void sendControlHeartbeat();
	bool isActivelyDriving = false;
	void setIsActivelyDriving(bool value) {
		isActivelyDriving = value; 
		sendControlHeartbeat();
	}
};
