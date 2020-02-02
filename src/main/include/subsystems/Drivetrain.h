#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/Spark.h"
#include "frc/Encoder.h"
#include <vector>

#include "RobotMap.h"

class Drivetrain : protected frc2::SubsystemBase {
	private:
	frc::Encoder* const leftEncoder = new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1]);
	frc::Encoder* const rightEncoder = new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1]);
	frc::SpeedController* const FLMotor = new frc::Spark(frontLeftMotorChannel);
	frc::SpeedController* const FRMotor = new frc::Spark(frontRightMotorChannel);
	frc::SpeedController* const BLMotor = new frc::Spark(backLeftMotorChannel);
	frc::SpeedController* const BRMotor = new frc::Spark(backRightMotorChannel);
	public:
	Drivetrain();
	void Drive(double left, double right);
	void DrivePolar(double power, double turn);
	double boundValue(double value, double bound);
	std::vector<double> getMotorPowers();
};