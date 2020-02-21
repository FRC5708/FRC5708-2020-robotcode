#pragma once

#include <frc2/command/SubsystemBase.h>
#include <vector>
#include <sys/socket.h>
#include <units/units.h>

class VisionReceiver : public frc2::SubsystemBase {
public:
	struct TargetData {
			TargetData()
			 : distance(0), tapeAngle(0), robotAngle(0) {}
			TargetData(units::inch_t _distance, units::radian_t _tapeAngle, units::radian_t _robotAngle) 
			 : distance(_distance), tapeAngle(_tapeAngle), robotAngle(_robotAngle) {}

			units::inch_t distance;
			// see 2020-vision/vision.hpp for descriptions
			units::radian_t tapeAngle, robotAngle;
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

};
